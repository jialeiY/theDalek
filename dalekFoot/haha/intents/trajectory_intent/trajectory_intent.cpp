#include "intents/trajectory_intent/trajectory_intent.h"
#include <array>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/polar_vector2d.h"
#include "data/defs/static_vector.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/topics.h"
#include "intents/trajectory_intent/trajectory/trajectory.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {


TrajectoryIntent::TrajectoryIntent() :
    passingPointList_ {},
    passingPointsOrientation_ {},
    trajectoryId_ {0U} {}
TrajectoryIntent::~TrajectoryIntent() {}
void TrajectoryIntent::setup() {
    trajectoryTopic.hasValue         = false;
    trajectoryTopic.passingPointSize = 0U;
    for (std::size_t i {0U}; i < TrajectoryTopic::kPassingPointCapacity; ++i) {
        data::PassingPoint &passingPoint {trajectoryTopic.passingPoint[i]};
        passingPoint.position = {0.0F, 0.0F};
    }
    trajectoryTopic.routeId = 0U;
}


// TrajectoryIntent reads the RouteTopic and output a runnable trajectory
void TrajectoryIntent::tick() {
    // Validate the route topic
    // bool isValid = Validate(routeTopic);

    // If route topic is valid and updated
    passingPointList_.reset();
    trajectory::generatePassingPointListBasedOnRoute(routeTopic.startPoint,
                                                     routeTopic.routeSegment,
                                                     routeTopic.routeSegmentSize,
                                                     passingPointList_);
    trajectory::calculatePassingPointsOrientation(passingPointList_, passingPointsOrientation_);
    outputTopic();
}

void TrajectoryIntent::outputTopic() {
    trajectoryTopic.hasValue         = true;
    trajectoryTopic.trajectoryId     = makeNewTrajectoryId();
    trajectoryTopic.passingPointSize = passingPointList_.size();
    for (std::size_t i {0U}; i < passingPointList_.size(); ++i) {
        trajectoryTopic.passingPoint[i].position    = passingPointList_[i];
        trajectoryTopic.passingPoint[i].orientation = passingPointsOrientation_[i];
    }
    trajectoryTopic.routeId = routeTopic.routeId;
}

TrajectoryId TrajectoryIntent::makeNewTrajectoryId() {
    trajectoryId_++;
    return trajectoryId_;
}

}    // namespace intent
}    // namespace cooboc