#include "intents/common/frenet.h"
#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace intent {
namespace frenet {

void locateSegmentInPolyline(const data::Position2D& poi,
                             const data::Position2D points[],
                             const std::size_t pointNumber) {
    // Find the segment..

    // There are three possible that poi could located in
    // 1. on the polyline
    // 2. before the polyline
    // 3. after the polyline
}
}    // namespace frenet
}    // namespace intent
}    // namespace cooboc