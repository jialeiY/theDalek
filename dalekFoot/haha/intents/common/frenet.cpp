#include "intents/common/frenet.h"
#include <cstdint>
#include "data/defs/position2d.h"


namespace cooboc {
namespace intent {
namespace frenet {

namespace detail {

// [) close open
bool isPoiCoveredBySegment(const data::Position2D& poi,
                           const data::Position2D& startPoint,
                           const data::Position2D& endPoint) {
    const bool isCoveredByStartPoint = {(poi - startPoint).dot(endPoint - startPoint) >= 0.0F};
    if (isCoveredByStartPoint) {
        return (poi - endPoint).dot(startPoint - endPoint) > 0.0F;    // Open so >
    }
    return false;
}
}    // namespace detail


}    // namespace frenet
}    // namespace intent
}    // namespace cooboc