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
    referencePathId_ {0U} {}
ReferencePathIntent::~ReferencePathIntent() {}
void ReferencePathIntent::setup() {
    referencePathTopic.hasValue         = false;
    referencePathTopic.passingPointSize = 0U;
    for (std::size_t i {0U}; i < kReferencePathPassingPointCapacity; ++i) {
        data::PassingPoint &passingPoint {referencePathTopic.passingPoint[i]};
        passingPoint.position = {0.0F, 0.0F};
    }
    referencePathTopic.routeId = 0U;
}


// ReferencePathIntent reads the RouteTopic and output a runnable trajectory
void ReferencePathIntent::tick() {
    // Validate the route topic
    // bool isValid = Validate(routeTopic);

    // If route topic is valid and updated
    // passingPointList_.reset();
    // reference_path::generatePassingPointListBasedOnRoute(routeTopic.startPoint,
    //                                                      routeTopic.routeSegment,
    //                                                      routeTopic.routeSegmentSize,
    //                                                      passingPointList_);
    // reference_path::calculatePassingPointsSegment(passingPointList_, passingPointsSegment_);
    // outputTopic();
}

void ReferencePathIntent::outputTopic() {
    referencePathTopic.hasValue         = true;
    referencePathTopic.referencePathId  = makeNewReferencePathId();
    referencePathTopic.passingPointSize = passingPointList_.size();
    for (std::size_t i {0U}; i < passingPointList_.size(); ++i) {
        referencePathTopic.passingPoint[i].position = passingPointList_[i];
        referencePathTopic.passingPoint[i].segment  = passingPointsSegment_[i];
    }
    referencePathTopic.routeId = routeTopic.id;
}

ReferencePathId ReferencePathIntent::makeNewReferencePathId() {
    referencePathId_++;
    return referencePathId_;
}

}    // namespace intent
}    // namespace cooboc