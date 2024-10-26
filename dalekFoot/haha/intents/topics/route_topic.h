#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/behavior_id.h"
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"
#include "data/defs/route_segment.h"
#include "data/defs/static_polyline_pod.h"

namespace cooboc {
namespace intent {


struct RouteTopic {
    static constexpr std::size_t kPolylineCapacity {100U};
    using Polyline = data::StaticPolylinePod<kPolylineCapacity>;

    data::RouteId id {data::kInvalidRouteId};

    data::BehaviorId behaviorId {data::kInvalidBehaviorId};

    Polyline polyline {};
    data::CurvatureDistribution connectivityProperties[kPolylineCapacity - 2U];
};
}    // namespace intent
}    // namespace cooboc

#endif
