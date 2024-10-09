#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/behavior_id.h"
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"
#include "data/defs/route_segment.h"

namespace cooboc {
namespace intent {


struct RouteTopic {
    static constexpr std::size_t kPolylineCapacity {100U};

    data::RouteId id {data::kInvalidRouteId};

    data::BehaviorId behaviorId {data::kInvalidBehaviorId};
    std::size_t pointsNumber {0U};
    data::Position2D points[kPolylineCapacity];
    data::CurvatureDistribution connectivityProperties[kPolylineCapacity - 2U];
};
}    // namespace intent
}    // namespace cooboc

#endif
