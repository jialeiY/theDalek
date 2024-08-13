#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/route_id.h"

namespace cooboc {
namespace intent {


struct RouteTopic {
    static constexpr std::size_t kPolylineCapacity {100U};

    bool hasValue;
    data::RouteId routeId;
    std::size_t polylineLength;
    data::Position2D polyline[kPolylineCapacity];
};
}    // namespace intent
}    // namespace cooboc

#endif
