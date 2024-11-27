#include "intents/reference_path_intent/reference_path_intent.h"
#include <array>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/polar_vector2d.h"
#include "data/defs/pose2d.h"
#include "data/defs/reference_path_id.h"
#include "data/defs/static_vector.h"
#include "intents/common/frenet.h"
#include "intents/reference_path_intent/components/sampling.h"
#include "intents/reference_path_intent/components/vertex_property.h"
#include "intents/topics/common.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {


ReferencePathIntent::ReferencePathIntent() : referencePathTopic_ {} {}
ReferencePathIntent::~ReferencePathIntent() {}
void ReferencePathIntent::setup() {
    resetCache();
    shared::referencePathTopic = referencePathTopic_;
}

void ReferencePathIntent::resetCache() {
    referencePathTopic_.id = data::kInvalidReferencePathId;
    referencePathTopic_.routeId = data::kInvalidRouteId;
    referencePathTopic_.pointsNumber = 0U;
    for (std::size_t i {0U}; i < ReferencePathTopic::kReferencePathPointsCapacity; ++i) {
        referencePathTopic_.points[i] = {0.0F, 0.0F};
    }

    // Reset the route profile
    for (std::size_t i {0U}; i < intent::RouteTopic::kPolylineCapacity; ++i) {
        routeProfile_[i].clear();
    }
}

// ReferencePathIntent reads the RouteTopic and output a runnable trajectory
void ReferencePathIntent::tick() {
    if (shared::routeTopic.id == data::kInvalidRouteId) {
        resetCache();
    } else {
        if (shared::routeTopic.id != referencePathTopic_.id) {
            reference_path::updateRouteProfile(shared::routeTopic, routeProfile_);
        } else {
            // do nothing, keep using cache
        }

        // TODO: update reference path
    }
    shared::referencePathTopic = referencePathTopic_;
}


void ReferencePathIntent::makeReferencePath(const OdometryTopic &odometryTopic,
                                            const RouteTopic &routeTopic) {
    frenet::locateSegmentInPolyline(odometryTopic.pose.position, routeTopic.polyline);

    // bool isRouteTopicValid {routeTopic.id != data::kInvalidRouteId};
    // bool isRoutePolylineValid {routeTopic.polyline.size > 1U};

    // const data::Pose2D &egoPose {odometryTopic.pose};

    // if (isRouteTopicValid && isRoutePolylineValid) {
    //     // Find out which route segment the ego is on
    //     frenet::locateSegmentInPolyline(egoPose.position, routeTopic.polyline);
    // } else {
    //     resetCache();
    // }
}


// void ReferencePathIntent::outputTopic() {
//     referencePathTopic.hasValue         = true;
//     referencePathTopic.referencePathId  = makeNewReferencePathId();
//     referencePathTopic.passingPointSize = passingPointList_.size();
//     for (std::size_t i {0U}; i < passingPointList_.size(); ++i) {
//         referencePathTopic.passingPoint[i].position = passingPointList_[i];
//         referencePathTopic.passingPoint[i].segment  = passingPointsSegment_[i];
//     }
//     referencePathTopic.routeId = routeTopic.id;
// }

// ReferencePathId ReferencePathIntent::makeNewReferencePathId() {
//     referencePathId_++;
//     return referencePathId_;
// }

}    // namespace intent
}    // namespace cooboc