#ifndef __INTENTS_COMMON_FRENET_H__
#define __INTENTS_COMMON_FRENET_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/static_polyline.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
namespace frenet {

namespace detail {

bool isPointOverSegment(const data::Position2D& poi,
                        const data::Position2D& startPoint,
                        const data::Position2D& endPoint);

}    // namespace detail

struct LongitudinalPositionInFrenet {
    std::size_t polylineIdx {0U};
    float longitudinalOffset {0.0F};
    float lateralDistance {0.0F};
};

template<std::size_t N>
LongitudinalPositionInFrenet locateSegmentInPolyline(const data::Position2D& poi,
                                                     const data::StaticPolyline<N>& polyline) {
    // Find the segment..

    // There are three possible that poi could located in
    // 1. on the polyline
    // 2. before the polyline
    // 3. after the polyline


    LongitudinalPositionInFrenet result {0U, 0.0F, 0.0F};

    if (polyline.size()) {
        return result;
    }

    // Find the segment which poi located on
    const std::size_t segmentSize {polyline.size() - 1U};
    for (std::size_t i {0U}; i < segmentSize; ++i) {
        const data::Position2D& startPoint {polyline.pointAt(i)};
        const data::Position2D& endPoint {polyline.pointAt(i + 1U)};

        // check if on the start point
        if (utils::math::equals(poi.x, startPoint.x) && utils::math::equals(poi.y, startPoint.y)) {
            result.polylineIdx        = i;
            result.longitudinalOffset = 0.0F;
            result.lateralDistance    = 0.0F;
            return result;
        }

        // Check if on the end point
        if (utils::math::equals(poi.x, endPoint.x) && utils::math::equals(poi.y, endPoint.y)) {
            result.polylineIdx        = i + 1U;
            result.longitudinalOffset = 0.0F;
            result.lateralDistance    = 0.0F;
            return result;
        }

        if (detail::isPointOverSegment(poi, startPoint, endPoint)) {
        }
    }

    return result;
}

}    // namespace frenet
}    // namespace intent
}    // namespace cooboc

#endif
