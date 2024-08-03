#ifndef __INTENTS_TOPICS_ROUTE_TOPIC_H__
#define __INTENTS_TOPICS_ROUTE_TOPIC_H__

#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {
struct RouteTopic {
    bool hasValue;
    std::uint64_t routeId;
    std::size_t polylineLength;
    data::Position2D polyline[100U];
};
}    // namespace intent
}    // namespace cooboc

#endif
