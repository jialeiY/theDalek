#include "intents/motion_planning_intent/motion_planning_intent.h"
#include <array>
#include <cstdio>
#include <iostream>
#include <limits>
#include <tuple>
#include "data/defs/pose2d.h"
#include "intents/motion_planning_intent/components/frenet.h"
#include "intents/motion_planning_intent/components/profile.h"
#include "intents/topics/topics.h"
#include "utils/algo/pid.h"
#include "utils/math.h"


namespace cooboc {

constexpr float kPlanningIntervalSeconds {0.01F};    // TODO: put parameter to parameter file

namespace intent {

MotionPlanningIntent::MotionPlanningIntent() :
    lateralPid_ {},
    curvatureProfile_ {},
    motionProfile_ {},
    poseInFrenet_ {},
    longitudinalPlanning_ {} {
    motionPlanningDebugTopic.numberOfWaypoints = 0U;
    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        motionPlanningDebugTopic.waypoints[i].pose      = {data::Position2D {0.0F, 0.0F}, 0.0F};
        motionPlanningDebugTopic.waypoints[i].timepoint = 0U;
    }
    motionPlanningDebugTopic.trajectoryPointIdx   = -1;
    motionPlanningDebugTopic.poseInFrenet         = data::Pose2D {};
    motionPlanningDebugTopic.distanceToTrajectory = 0.0F;
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

constexpr float kMaximumAcceleration = 0.5F;    // m/s
constexpr float kMaximumVelocity     = 1.0F;    // m/s
void MotionPlanningIntent::tick() {
    // Calculate curvature profile
    curvatureProfile_.reset();
    motion_planning::calculateCurvatureProfile(
      trajectoryTopic.passingPoint, trajectoryTopic.passingPointSize, curvatureProfile_);

    // Calculate the motion profile for longitudinal

    motionProfile_.reset();
    motion_planning::calculateMotionProfile(
      curvatureProfile_, kMaximumAcceleration, kMaximumVelocity, motionProfile_);

    // Calculate the position in frenet
    // TODO: check the length of trajectory
    std::size_t idx;
    float dist;
    std::tie(idx, dist) = motion_planning::calculatePoseInFrenet(odometryTopic.pose,
                                                                 trajectoryTopic.passingPoint,
                                                                 trajectoryTopic.passingPointSize,
                                                                 poseInFrenet_);


    // Find out longitudinal and Lateral speed
    data::PolarVector2D egoVelocity = egoStateTopic.velocity;
    egoVelocity.orientation         = egoVelocity.orientation + poseInFrenet_.orientation;
    data::Vector2D resolvedVelocity = utils::math::to<data::Vector2D>(egoVelocity);

    // data::PolarVector2D egoAcceleration = egoStateTopic.acceleration;
    // egoAcceleration.orientation         = egoAcceleration.orientation -
    // poseInFrenet_.orientation; data::Vector2D resolvedAcceleration =
    // utils::math::to<data::Vector2D>(egoAcceleration); Plan longitudinal

    // planLongitudinal(poseInFrenet_.position.x, resolvedVelocity.x, resolvedAcceleration.x, idx);
    planLongitudinal(poseInFrenet_.position.x, resolvedVelocity.x);

    // Output to topic
    for (std::size_t i {0U}; i < kPlanningSize; ++i) {
        data::Waypoint &wp {(motionPlanningTopic.waypoints)[i]};
        wp.velocity.x = longitudinalPlanning_[i].motionVelocity.x;
        wp.velocity.y = longitudinalPlanning_[i].motionVelocity.y;
    }

    // Output to debug
    for (std::size_t i {0U}; i < kTrajectoryPassingPointCapacity; ++i) {
        motionPlanningDebugTopic.longitudinalCurvatureProfile[i] = curvatureProfile_[i];
        motionPlanningDebugTopic.longitudinalMotionProfile[i]    = motionProfile_[i];
    }
    motionPlanningDebugTopic.trajectoryPointIdx   = idx;
    motionPlanningDebugTopic.poseInFrenet         = poseInFrenet_;
    motionPlanningDebugTopic.distanceToTrajectory = dist;
}


void MotionPlanningIntent::planLongitudinal(const float initS, const float initSpeed) {
    std::size_t idx         = 0U;
    float segmentS          = initS;
    float longitudinalSpeed = initSpeed;

    normalizeS(idx, segmentS);
    data::Position2D position = mapSToPosition(idx, segmentS);

    for (std::size_t i {0}; i < kPlanningSize; ++i) {
        // 1. Deduce speed
        float maximumSegmentSpeed {0.0F};
        float maximumSegmentAcceleration {0.0F};
        std::tie(maximumSegmentSpeed, maximumSegmentAcceleration) = motionProfile_[idx];
        const float maximumAllowedSpeedDiff =
          (maximumSegmentAcceleration * kPlanningIntervalSeconds);
        const float maxAllowedSpeed = longitudinalSpeed + maximumAllowedSpeedDiff;
        const float minAllowedSpeed = longitudinalSpeed - maximumAllowedSpeedDiff;

        longitudinalSpeed =
          std::max(std::min(maximumSegmentSpeed, maxAllowedSpeed), minAllowedSpeed);


        segmentS += longitudinalSpeed * kPlanningIntervalSeconds;
        normalizeS(idx, segmentS);
        const data::Position2D nextPosition = mapSToPosition(idx, segmentS);
        const data::Vector2D motionDistance = nextPosition - position;
        const data::Vector2D motionVelocity = motionDistance / kPlanningIntervalSeconds;

        // Output
        LongitudinalPlanningPoint &lpp = longitudinalPlanning_[i];
        lpp.trajectoryIdx              = idx;
        lpp.segmentS                   = segmentS;
        lpp.speed                      = longitudinalSpeed;
        lpp.waypoint                   = nextPosition;

        lpp.motionVelocity = motionVelocity;


        // Update status
        position = nextPosition;
    }
}

void MotionPlanningIntent::normalizeS(std::size_t &trajectoryIdx, float &s) {
    if (s < 0.0F) {
        trajectoryIdx = 0U;
    }

    while ((trajectoryIdx + 2U) < trajectoryTopic.passingPointSize) {
        const float &currentSegmentLength {
          trajectoryTopic.passingPoint[trajectoryIdx + 1U].segment.value};
        if (currentSegmentLength < s) {
            s -= currentSegmentLength;
            trajectoryIdx++;
        } else {
            break;
        }
    }
}

data::Position2D MotionPlanningIntent::mapSToPosition(std::size_t &trajectoryIdx, const float s) {
    if ((trajectoryIdx + 1U) < trajectoryTopic.passingPointSize) {
        const data::Position2D &startPoint {trajectoryTopic.passingPoint[trajectoryIdx].position};
        const data::Position2D &endPoint {
          trajectoryTopic.passingPoint[trajectoryIdx + 1U].position};
        const float length     = trajectoryTopic.passingPoint[trajectoryIdx + 1U].segment.value;
        const float percentage = s / length;
        return utils::math::interpolate(startPoint, endPoint, percentage);
    } else {
        // TODO: error here
        return {0.0F, 0.0F};
    }
}

}    // namespace intent
}    // namespace cooboc