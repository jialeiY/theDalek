#include "intents/motion_planning_intent/motion_planning_intent.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <limits>
#include "data/defs/pose2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {

namespace detail {
ReferencePose calculatePositionInFrene(const data::Pose2D &odometry, const RouteTopic &route) {
    // TODO, assume route always has data now

    // Find the segment
    std::size_t closestSegmentId {0U};
    float closestDistance {std::numeric_limits<float>::max()};

    const std::size_t segmentNumber = route.polylineLength - 1U;
    for (std::size_t i {0U}; i < segmentNumber; ++i) {
        bool firstNeedOpen = i != 0U;    // only first one open
        float dist         = std::fabs(calculateDistanceFromPointToSegment(
          odometry.position, route.polyline[i], route.polyline[i + 1U], firstNeedOpen, true));
        if (dist < closestDistance) {
            closestSegmentId = i;
            closestDistance  = dist;
        }
    }


    float s = 0.0F;
    // Calculate all s before current segment
    for (std::size_t i {0U}; (i + 1U) < closestSegmentId; ++i) {
        s += route.polyline[i].distance(route.polyline[i + 1U]);
    }

    // Calculate s on current segment
    if (!utils::math::equals(route.polyline[closestSegmentId],
                             route.polyline[closestSegmentId + 1U])) {
        const data::Position2D veca =
          route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId];
        const data::Position2D vecb = odometry.position - route.polyline[closestSegmentId];
        s += veca.dot(vecb) / veca.abs();
    }

    const float y {calculateDistanceFromPointToSegment(odometry.position,
                                                       route.polyline[closestSegmentId],
                                                       route.polyline[closestSegmentId + 1U],
                                                       false,
                                                       false)};

    data::Vector2D refSegVec {
      (route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId])};
    data::PolarVector2D refSegPolarVec = utils::math::to<data::PolarVector2D>(refSegVec);
    std::cout << "closestSegmentId: " << closestSegmentId << " vec(" << refSegVec.x << ","
              << refSegVec.y << ")" << std::endl;
    std::cout << "ref seg ori: " << refSegPolarVec.orientation << std::endl;

    return {s, y, refSegPolarVec.orientation};
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


MotionPlanningIntent::MotionPlanningIntent() {
    motionPlanningDebugTopic.numberOfWaypoints = 0U;
    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        motionPlanningDebugTopic.waypoints[i].pose      = {data::Position2D {0.0F, 0.0F}, 0.0F};
        motionPlanningDebugTopic.waypoints[i].timepoint = 0U;
    }
}
MotionPlanningIntent::~MotionPlanningIntent() {}
void MotionPlanningIntent::setup() {}


void MotionPlanningIntent::tick() {
    std::cout << std::endl << std::endl << "=======" << std::endl;
    // 0. Setup the input data
    // Odometry
    const data::Pose2D &odometry = odometryTopic.pose;
    // Reference path
    const RouteTopic &route = routeTopic;

    // 1. key reference path where odometry is on it
    detail::ReferencePose refPose = detail::calculatePositionInFrene(odometry, route);

    data::Pose2D initOdometryInFrenet {{refPose.s, refPose.y},
                                       odometryTopic.pose.orientation - refPose.orientation};
    data::PolarVector2D initVelocityInFrenet {
      egoStateTopic.velocity.orientation - refPose.orientation, egoStateTopic.velocity.value};
    data::PolarVector2D initAccelerationInFrenet {
      egoStateTopic.acceleration.orientation - refPose.orientation,
      egoStateTopic.acceleration.value};
    std::cout << "velo orig: " << egoStateTopic.velocity.orientation
              << " ref ori: " << refPose.orientation << std::endl;
    std::cout << "velo in Frenet: " << initVelocityInFrenet.orientation
              << " v: " << initVelocityInFrenet.value << std::endl;

    planEgoMotion(initOdometryInFrenet, initVelocityInFrenet, initAccelerationInFrenet);
}

void MotionPlanningIntent::planEgoMotion(const data::Pose2D &inintOdometry,
                                         const data::PolarVector2D &initVelocity,
                                         const data::PolarVector2D &initAcceleration) {
    // Generate trajectory of 100 waypoints

    motionPlanningDebugTopic.numberOfWaypoints = 100U;

    // lateral first

    std::array<float, 100U> lateralPositionList;
    data::Vector2D splitVelocity     = utils::math::to<data::Vector2D>(initVelocity);
    data::Vector2D splitAcceleration = utils::math::to<data::Vector2D>(initAcceleration);

    data::Pose2D egoPose {inintOdometry};

    std::cout << "vy: " << splitVelocity.y << std::endl;

    for (std::size_t i {0U}; i < 100; ++i) {
        data::Waypoint &waypoint {motionPlanningDebugTopic.waypoints[i]};
        waypoint.timepoint = odometryTopic.timestamp + (10U * 1000U * i);    // 10 ms

        egoPose.position.y += splitVelocity.y * 0.01;

        waypoint.pose = egoPose;
    }
}


}    // namespace intent
}    // namespace cooboc