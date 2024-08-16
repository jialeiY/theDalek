#include "intents/motion_planning_intent/motion_planning_intent.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <limits>
#include "data/defs/pose2d.h"
#include "intents/topics/topics.h"
#include "utils/algo/pid.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {

namespace detail {
ReferencePose calculatePositionInFrenet(const data::Pose2D &odometry, const RouteTopic &route) {
    // // TODO, assume route always has data now

    // // Find the segment
    // std::size_t closestSegmentId {0U};
    // float closestDistance {std::numeric_limits<float>::max()};

    // const std::size_t segmentNumber = route.polylineLength - 1U;
    // for (std::size_t i {0U}; i < segmentNumber; ++i) {
    //     bool firstNeedOpen = i != 0U;    // only first one open
    //     float dist         = std::fabs(calculateDistanceFromPointToSegment(
    //       odometry.position, route.polyline[i], route.polyline[i + 1U], firstNeedOpen, true));
    //     if (dist < closestDistance) {
    //         closestSegmentId = i;
    //         closestDistance  = dist;
    //     }
    // }


    // float s = 0.0F;
    // // Calculate all s before current segment
    // for (std::size_t i {0U}; (i + 1U) < closestSegmentId; ++i) {
    //     s += route.polyline[i].distance(route.polyline[i + 1U]);
    // }

    // // Calculate s on current segment
    // if (!utils::math::equals(route.polyline[closestSegmentId],
    //                          route.polyline[closestSegmentId + 1U])) {
    //     const data::Position2D veca =
    //       route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId];
    //     const data::Position2D vecb = odometry.position - route.polyline[closestSegmentId];
    //     s += veca.dot(vecb) / veca.abs();
    // }

    // const float y {calculateDistanceFromPointToSegment(odometry.position,
    //                                                    route.polyline[closestSegmentId],
    //                                                    route.polyline[closestSegmentId + 1U],
    //                                                    false,
    //                                                    false)};

    // data::Vector2D refSegVec {
    //   (route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId])};
    // data::PolarVector2D refSegPolarVec = utils::math::to<data::PolarVector2D>(refSegVec);
    // return {s, y, refSegPolarVec.orientation};
    return {};
}

float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed,
                                          const bool isEndClosed) {
    // Is start equals to end
    if (utils::math::equals(segmentStart, segmentEnd)) {
        return point.distance(segmentStart);
    }

    // is on the start point?
    if (utils::math::equals(point.x, segmentStart.x) &&
        utils::math::equals(point.y, segmentStart.y)) {
        return 0.0F;
    }

    // is on the end point?
    if ((utils::math::equals(point.x, segmentEnd.x)) &&
        (utils::math::equals(point.y, segmentEnd.y))) {
        return 0.0F;
    }

    // Point out side of start
    if (isStartClosed) {
        if ((point - segmentStart).dot(segmentEnd - segmentStart) < 0.0F) {
            return point.distance(segmentStart);
        }
    }

    // Point out side of end
    if (isEndClosed) {
        if ((point - segmentEnd).dot(segmentStart - segmentEnd) < 0.0F) {
            return point.distance(segmentEnd);
        }
    }

    // // the representation of line is Ax + By + C = 0;
    // // d = |Ax + Ｂy + C| / sqrt(A^2 + B^2)
    // const float A = (segmentEnd.y - segmentStart.y);
    // const float B = (segmentStart.x - segmentEnd.x);
    // const float C =
    //   (segmentEnd.x * segmentStart.y) - (segmentStart.x * segmentEnd.y);
    // const float dist2line = std::fabs((A * point.x) + (B * point.y) + C) /
    //                         std::sqrt((A * A) + (B * B));
    const float dist2line =
      ((segmentEnd - segmentStart).cross(point - segmentStart)) / segmentStart.distance(segmentEnd);
    return dist2line;
}

}    // namespace detail


MotionPlanningIntent::MotionPlanningIntent() : lateralPid_ {} {
    motionPlanningDebugTopic.numberOfWaypoints = 0U;
    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        motionPlanningDebugTopic.waypoints[i].pose      = {data::Position2D {0.0F, 0.0F}, 0.0F};
        motionPlanningDebugTopic.waypoints[i].timepoint = 0U;
    }
}
MotionPlanningIntent::~MotionPlanningIntent() {}

void MotionPlanningIntent::setup() {
    constexpr float kLateralP {3.0F};    // 3 is the optimized number
    constexpr float kLateralI {0.0F};
    constexpr float kLateralD {60.0F};
    // Make it to parameter file
    lateralPid_.updatePID(kLateralP, kLateralI, kLateralD);
    lateralPid_.reset();
}


void MotionPlanningIntent::tick() {
    std::cout << std::endl << std::endl << "=======" << std::endl;
    // 0. Setup the input data
    // Odometry
    const data::Pose2D &odometry = odometryTopic.pose;
    // Reference path
    const RouteTopic &route = routeTopic;

    // 1. key reference path where odometry is on it
    detail::ReferencePose refPose = detail::calculatePositionInFrenet(odometry, route);

    data::Pose2D initOdometryInFrenet {{refPose.s, refPose.y},
                                       odometryTopic.pose.orientation - refPose.orientation};
    data::PolarVector2D initVelocityInFrenet {
      egoStateTopic.velocity.orientation + odometry.orientation - refPose.orientation,
      egoStateTopic.velocity.value};
    data::PolarVector2D initAccelerationInFrenet {
      egoStateTopic.acceleration.orientation + odometry.orientation - refPose.orientation,
      egoStateTopic.acceleration.value};

    planEgoMotion(initOdometryInFrenet, initVelocityInFrenet, initAccelerationInFrenet);
}

void MotionPlanningIntent::planEgoMotion(const data::Pose2D &initOdometry,
                                         const data::PolarVector2D &initVelocity,
                                         const data::PolarVector2D &initAcceleration) {
    // Generate trajectory of waypoints
    motionPlanningDebugTopic.numberOfWaypoints = MotionPlanningDebugTopic::kWaypointNumber;

    // lateral first
    data::Vector2D splitVelocity     = utils::math::to<data::Vector2D>(initVelocity);
    data::Vector2D splitAcceleration = utils::math::to<data::Vector2D>(initAcceleration);

    data::Pose2D egoPose {initOdometry};

    // Way point [0] is the init state that can not changed. Based on the init state, this module
    // send the control signal to control the states following that.
    // The velocity and acceleration is the control signal for changing this state. That means the
    // velocity and acceleration is the motion state that the vehicle must to reach in the next
    // cycle.
    // And the Planner plans the waypoint 5 times of the vehicle that. It means haha generates the
    // cycles number is 10ms(gaga cycle), 5second planning = 500 waypoints.

    // Initialize the velocity and acceleration
    motionPlanningDebugTopic.numberOfWaypoints = MotionPlanningDebugTopic::kWaypointNumber;

    float lastVy = splitVelocity.y;
    float lastAy = splitAcceleration.y;

    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        data::Waypoint &waypoint {motionPlanningDebugTopic.waypoints[i]};
        waypoint.timepoint = odometryTopic.timestamp + (100U * 1000U * i);    // 10 ms

        // 1. Write out current Status
        waypoint.pose = egoPose;

        // 2. Calculate the maneuver state
        // Update lateral position based on velocity
        float egoy {egoPose.position.y};
        // Calculate the control value
        float error {0 - egoPose.position.y};
        lateralPid_.updateError(error);
        float expectV {lateralPid_.getOutput()};
        float expectA {(expectV - lastVy) * 100.0F};    // 10ms

        // 3. Constrains the maneuver not too ridiculous
        float actualA {utils::math::clamp(expectA, -0.3F, 0.3F)};
        float actualV {lastVy + (actualA * 0.01F)};    // 10ms

        // 3. Write out maneuver state
        waypoint.velocityY     = actualV;
        waypoint.accelerationY = actualA;
        lastVy                 = actualV;

        // 4. Update ego for next waypoint
        egoy += actualV * 0.01F;    // 10ms
        egoPose.position.y = egoy;
    }
}


}    // namespace intent
}    // namespace cooboc