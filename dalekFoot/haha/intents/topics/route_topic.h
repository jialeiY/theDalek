#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/position2d.h"


namespace cooboc {
namespace intent {

using RouteId = std::uint64_t;


struct RouteTopic {
    static constexpr std::size_t kPolylineLength {100U};

    bool hasValue;
    RouteId routeId;
    std::size_t polylineLength;
    data::Position2D polyline[kPolylineLength];
};
}    // namespace intent
}    // namespace cooboc

#endif
