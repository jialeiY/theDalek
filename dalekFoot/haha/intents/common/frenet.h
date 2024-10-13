#ifndef __INTENTS_COMMON_FRENET_H__
#define __INTENTS_COMMON_FRENET_H__

#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {
namespace frenet {

struct LongitudinalPositionInFrenet {
    std::size_t polylineIdx {0U};
    float offset {0.0F};
};

void locateSegmentInPolyline(const data::Position2D& poi,
                             const data::Position2D points[],
                             const std::size_t pointNumber);

}    // namespace frenet
}    // namespace intent
}    // namespace cooboc

#endif
