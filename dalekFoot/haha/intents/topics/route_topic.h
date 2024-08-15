#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"
#include "data/defs/route_segment.h"

namespace cooboc {
namespace intent {


struct RouteTopic {
    static constexpr std::size_t kPolylineCapacity {100U};

    bool hasValue {false};
    data::RouteId routeId {0U};
    std::size_t polylineLength {0U};
    data::Position2D startPoint {};

    data::RouteSegment routeSegment[kPolylineCapacity];
};
}    // namespace intent
}    // namespace cooboc

#endif
