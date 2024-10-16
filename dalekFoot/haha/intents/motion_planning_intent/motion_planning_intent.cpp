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
    shadowVehicle_ {},
    lateralPid_ {},
    curvatureProfile_ {},
    motionProfile_ {},
    poseInFrenet_ {},
    longitudinalPlanning_ {} {
    // Invalidate shadow vehicle
    shadowVehicle_.setValid(false);

    shared::motionPlanningDebugTopic.numberOfWaypoints = 0U;
    for (std::size_t i {0U}; i < MotionPlanningDebugTopic::kWaypointNumber; ++i) {
        shared::motionPlanningDebugTopic.waypoints[i].pose = {data::Position2D {0.0F, 0.0F}, 0.0F};
        shared::motionPlanningDebugTopic.waypoints[i].timepoint = 0U;
    }
    shared::motionPlanningDebugTopic.trajectoryPointIdx   = -1;
    shared::motionPlanningDebugTopic.poseInFrenet         = data::Pose2D {};
    shared::motionPlanningDebugTopic.distanceToTrajectory = 0.0F;
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

constexpr float kMaximumAcceleration = 0.3F;    // m/s
constexpr float kMaximumVelocity     = 0.3F;    // m/s
void MotionPlanningIntent::tick() {
    plan();
}


void MotionPlanningIntent::plan() {
    // // Calculate curvature profile
    // curvatureProfile_.reset();
    // motion_planning::calculateCurvatureProfile(
    //   referencePathTopic.passingPoint, referencePathTopic.passingPointSize, curvatureProfile_);

    // // Calculate the motion profile for longitudinal

    // motionProfile_.reset();
    // motion_planning::calculateMotionProfile(
    //   curvatureProfile_, kMaximumAcceleration, kMaximumVelocity, motionProfile_);

    // // Calculate the position in frenet
    // // TODO: check the length of trajectory
    // std::size_t idx;
    // float dist;

    // const data::VehicleState initState = getInitVehicleState();
    // std::printf("init pos(%f, %f)\r\n", initState.pose.position.x, initState.pose.position.y);
    // std::tie(idx, dist) =
    //   motion_planning::calculatePoseInFrenet(initState.pose,
    //                                          referencePathTopic.passingPoint,
    //                                          referencePathTopic.passingPointSize,
    //                                          poseInFrenet_);
    // // Find out longitudinal and Lateral speed
    // // data::PolarVector2D egoVelocity = egoMotionStateTopic.velocity;
    // // egoVelocity.orientation         = egoVelocity.orientation + poseInFrenet_.orientation;
    // // data::Vector2D resolvedVelocity = utils::math::to<data::Vector2D>(egoVelocity);

    // data::PolarVector2D egoVelocityInWorld = initState.motionState.velocity;
    // egoVelocityInWorld.orientation = egoVelocityInWorld.orientation + poseInFrenet_.orientation;
    // const data::Vector2D resolvedVelocity = utils::math::to<data::Vector2D>(egoVelocityInWorld);

    // // planLongitudinal(poseInFrenet_.position.x, resolvedVelocity.x, resolvedAcceleration.x,
    // idx); planLongitudinal(poseInFrenet_.position.x, resolvedVelocity.x);

    // // Update Shadow

    // data::MotionState motionState {};
    // motionState.velocity =
    //   utils::math::to<data::PolarVector2D>(longitudinalPlanning_[0].motionVelocity);

    // data::Pose2D nextPose = shadowVehicle_.getVehicleState().pose;
    // nextPose.position     = nextPose.position + motionState.velocity * 0.01F;
    // //{longitudinalPlanning_[1U].waypoint, 0.0F};
    // shadowVehicle_.setPose(nextPose);
    // shadowVehicle_.setMotionState(motionState);

    // // Output to topic
    // for (std::size_t i {0U}; i < kPlanningSize; ++i) {
    //     data::Waypoint &wp {(motionPlanningTopic.waypoints)[i]};
    //     wp.velocity.x = longitudinalPlanning_[i].motionVelocity.x;
    //     wp.velocity.y = longitudinalPlanning_[i].motionVelocity.y;
    // }

    // // Output to debug
    // for (std::size_t i {0U}; i < kReferencePathPassingPointCapacity; ++i) {
    //     motionPlanningDebugTopic.longitudinalCurvatureProfile[i] = curvatureProfile_[i];
    //     motionPlanningDebugTopic.longitudinalMotionProfile[i]    = motionProfile_[i];
    // }
    // motionPlanningDebugTopic.trajectoryPointIdx   = idx;
    // motionPlanningDebugTopic.poseInFrenet         = poseInFrenet_;
    // motionPlanningDebugTopic.distanceToTrajectory = dist;
}

data::VehicleState MotionPlanningIntent::getInitVehicleState() {
    // choose from shadow or from odometry
    if (isEgoStateDifferenceTooBig()) {
        synchronizeEgoWithShadow();
    }
    return shadowVehicle_.getVehicleState();
}

bool MotionPlanningIntent::isEgoStateDifferenceTooBig() {
    return !shadowVehicle_.isValid();    // || egoAndShadowDiffLarge
}

void MotionPlanningIntent::synchronizeEgoWithShadow() {
    const data::Pose2D &pose {shared::odometryTopic.pose};
    const data::MotionState &motionState {shared::egoMotionStateTopic};

    shadowVehicle_.setPose(pose);
    shadowVehicle_.setMotionState(motionState);
    shadowVehicle_.setValid(true);
}

void MotionPlanningIntent::planLongitudinal(const float initS, const float initSpeed) {
    std::size_t idx         = 0U;
    float segmentS          = initS;
    float longitudinalSpeed = initSpeed;

    normalizeS(idx, segmentS);
    data::Position2D position {};
    bool isReachEnd {false};
    std::tie(position, isReachEnd) = mapSToPosition(idx, segmentS);


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
        data::Position2D nextPosition {};
        bool isReachEnd {false};
        std::tie(nextPosition, isReachEnd) = mapSToPosition(idx, segmentS);


        if (isReachEnd) {
            // stop the vehicle
            nextPosition = position;
        }

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
    // if (s < 0.0F) {
    //     trajectoryIdx = 0U;
    // }

    // while ((trajectoryIdx + 2U) < referencePathTopic.passingPointSize) {
    //     const float &currentSegmentLength {
    //       referencePathTopic.passingPoint[trajectoryIdx + 1U].segment.value};
    //     if (currentSegmentLength < s) {
    //         s -= currentSegmentLength;
    //         trajectoryIdx++;
    //     } else {
    //         break;
    //     }
    // }
}

std::tuple<data::Position2D, bool> MotionPlanningIntent::mapSToPosition(std::size_t &trajectoryIdx,
                                                                        const float s) {
    // if ((trajectoryIdx + 1U) < referencePathTopic.passingPointSize) {
    //     const data::Position2D &startPoint {
    //       referencePathTopic.passingPoint[trajectoryIdx].position};
    //     const data::Position2D &endPoint {
    //       referencePathTopic.passingPoint[trajectoryIdx + 1U].position};
    //     const float length     = referencePathTopic.passingPoint[trajectoryIdx +
    //     1U].segment.value; const float percentage = s / length; return
    //     {utils::math::interpolate(startPoint, endPoint, percentage), percentage >= 1.0F};
    // } else {
    //     // TODO: error here
    return {{0.0F, 0.0F}, false};
    // }
}

}    // namespace intent
}    // namespace cooboc