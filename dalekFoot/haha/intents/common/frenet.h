#ifndef __INTENTS_COMMON_FRENET_H__
#define __INTENTS_COMMON_FRENET_H__

#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {
namespace frenet {

void locateSegmentInPolyline(const data::Position2D& poi,
                             const data::Position2D points[],
                             const std::size_t pointNumber);

}
}    // namespace intent
}    // namespace cooboc

#endif
