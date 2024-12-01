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
        // TODO: validate route?
        if (shared::routeTopic.id != referencePathTopic_.routeId) {
            reference_path::updateRouteProfile(shared::routeTopic, routeProfile_);
        } else {
            // do nothing, keep using cache
        }

        const data::Position2D &egoPos {shared::odometryTopic.pose.position};
        const intent::RouteTopic::Polyline &route {shared::routeTopic.polyline};
        const frenet::PositionInFrenetPolyline egoPosInFrenet = frenet::locateSegmentInPolyline(egoPos, route);
        std::int32_t routeIdx = egoPosInFrenet.polylineIdx;
        std::size_t beginIdx = static_cast<std::size_t>(std::max(routeIdx - 1, 0));
        std::int32_t segmentNumber = shared::routeTopic.polyline.length() - 1U;
        std::size_t endIdx = static_cast<std::size_t>(std::min(routeIdx + 2, segmentNumber));

        if (needUpdateReferencePath(shared::routeTopic.id, beginIdx, endIdx)) {
            makeReferencePath(beginIdx, endIdx);
        }
    }
    shared::referencePathTopic = referencePathTopic_;
}

bool ReferencePathIntent::needUpdateReferencePath(const data::RouteId &routeId,
                                                  const std::size_t &beginRouteIdx,
                                                  const std::size_t &endRouteIdx) const {
    if (referencePathTopic_.id == data::kInvalidReferencePathId) {
        return true;
    }

    if ((referencePathTopic_.routeId == routeId) && (referencePathTopic_.beginRouteIdx == beginRouteIdx) &&
        (referencePathTopic_.endRouteIdx == endRouteIdx)) {
        return false;
    }

    return true;
}


void ReferencePathIntent::makeReferencePath(const data::RouteId &routeId,
                                            const std::size_t beginIdx,
                                            const std::size_t endIdx) {
    referencePathTopic_.id = makeReferencePathId();
    referencePathTopic_.routeId = routeId;
    referencePathTopic_.beginRouteIdx = beginIdx;
    referencePathTopic_.endRouteIdx = endIdx;

    data::StaticPolylinePod<ReferencePathTopic::kReferencePathPointsCapacity> polyline;
    // Put the first point
    polyline.push_back(routeProfile_[0U][0U]);
    for (std::size_t i {beginIdx}; i < endIdx; ++i) {
        makeSegmentByProfile(routeProfile_[i], );
    }
}


data::ReferencePathId ReferencePathIntent::makeReferencePathId() const {
    static data::ReferencePathId id {1U};
    return id++;
}

void ReferencePathIntent::makeSegmentByProfile(const std::vector<data::Position2D> &routeSegmentProfile,
                                               ReferencePathTopic::Points &points,
                                               size_t outputIndex) const {}


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