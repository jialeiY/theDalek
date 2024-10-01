#include "intents/reference_path_intent/reference_path_intent.h"
#include <array>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/polar_vector2d.h"
#include "data/defs/static_vector.h"
#include "intents/reference_path_intent/components/sampling.h"
#include "intents/topics/common.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {


ReferencePathIntent::ReferencePathIntent() :
    passingPointList_ {},
    passingPointsSegment_ {},
    trajectoryId_ {0U} {}
ReferencePathIntent::~ReferencePathIntent() {}
void ReferencePathIntent::setup() {
    trajectoryTopic.hasValue         = false;
    trajectoryTopic.passingPointSize = 0U;
    for (std::size_t i {0U}; i < kTrajectoryPassingPointCapacity; ++i) {
        data::PassingPoint &passingPoint {trajectoryTopic.passingPoint[i]};
        passingPoint.position = {0.0F, 0.0F};
    }
    trajectoryTopic.routeId = 0U;
}


// ReferencePathIntent reads the RouteTopic and output a runnable trajectory
void ReferencePathIntent::tick() {
    // Validate the route topic
    // bool isValid = Validate(routeTopic);

    // If route topic is valid and updated
    passingPointList_.reset();
    reference_path::generatePassingPointListBasedOnRoute(routeTopic.startPoint,
                                                         routeTopic.routeSegment,
                                                         routeTopic.routeSegmentSize,
                                                         passingPointList_);
    reference_path::calculatePassingPointsSegment(passingPointList_, passingPointsSegment_);
    outputTopic();
}

void ReferencePathIntent::outputTopic() {
    trajectoryTopic.hasValue         = true;
    trajectoryTopic.trajectoryId     = makeNewTrajectoryId();
    trajectoryTopic.passingPointSize = passingPointList_.size();
    for (std::size_t i {0U}; i < passingPointList_.size(); ++i) {
        trajectoryTopic.passingPoint[i].position = passingPointList_[i];
        trajectoryTopic.passingPoint[i].segment  = passingPointsSegment_[i];
    }
    trajectoryTopic.routeId = routeTopic.routeId;
}

TrajectoryId ReferencePathIntent::makeNewTrajectoryId() {
    trajectoryId_++;
    return trajectoryId_;
}

}    // namespace intent
}    // namespace cooboc