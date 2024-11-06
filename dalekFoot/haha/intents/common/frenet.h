#ifndef __INTENTS_COMMON_FRENET_H__
#define __INTENTS_COMMON_FRENET_H__

#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/static_polyline_pod.h"
#include "data/defs/static_vector.h"
#include "utils/math.h"


namespace cooboc {

namespace intent {
namespace frenet {

namespace detail {

// [) close open
bool isPoiCoveredBySegment(const data::Position2D& poi,
                           const data::Position2D& startPoint,
                           const data::Position2D& endPoint);

}    // namespace detail

struct PositionInFrenetPolyline {
    std::size_t polylineIdx {0U};
    float longitudinalOffset {0.0F};
    float lateralDistance {0.0F};
};


template<std::size_t N>
PositionInFrenetPolyline locateSegmentInPolyline(const data::Position2D& poi,
                                                 const data::StaticPolylinePod<N>& polyline) {
    // Find the segment..

    /** Main idea to find the segment where the poi locate on
     * 1. Check whether poi exactly on the vertex to avoid divide0 exception
     * 2. find the closest distance from poi to segment, if poi is on the cover of segment
     * 3. find the closest distance from poi to vertex.
     * 4. if the closest distance is poi to end vertex, then the index is endvertex, the reference
     * segment is extention of last segment
     * 5. If closest distance is poi to segment, then frenet coordinate based on this segment.
     * 6. If closest distance is from poi to vertex, the the reference segment is the segment start
     * with this vertex.
     */


    // There are three possible that poi could located in
    // 1. on the polyline
    // 2. before the polyline
    // 3. after the polyline


    PositionInFrenetPolyline result {0U, 0.0F, 0.0F};

    if (polyline.length() < 2U) {
        return result;
    }


    // Check if poi on vertex
    for (std::size_t i {0U}; i < polyline.length(); ++i) {
        if (utils::math::equals(poi, polyline.at(i))) {
            result.polylineIdx        = i;
            result.longitudinalOffset = 0.0F;
            result.lateralDistance    = 0.0F;
            return result;
        }
    }

    // // Check if poi on the last point
    // if (utils::math::equals(poi, polyline.back())) {
    //     const data::Position2D& startPoint {polyline.at(polyline.length() - 2U)};
    //     const data::Position2D& endPoint {polyline.at(polyline.length() - 1U)};
    //     result.polylineIdx        = segmentSize;
    //     result.longitudinalOffset = startPoint.distance(endPoint);
    //     result.lateralDistance    = 0.0F;
    //     return result;
    // }


    // Find the segment which poi located on
    const std::size_t segmentSize {polyline.length() - 1U};
    std::int32_t closestSegmentIdx {-1};
    float closestSegmentLongitudinal {0.0F};
    float closestSegmentLateral {0.0F};
    for (std::size_t i {0U}; i < segmentSize; ++i) {
        const data::Position2D& startPoint {polyline.at(i)};
        const data::Position2D& endPoint {polyline.at(i + 1U)};

        if (detail::isPoiCoveredBySegment(poi, startPoint, endPoint)) {
            // // the representation of line is Ax + By + C = 0;
            // // d = |Ax + Ｂy + C| / sqrt(A^2 + B^2)
            // const float A = (segmentEnd.y - segmentStart.y);
            // const float B = (segmentStart.x - segmentEnd.x);
            // const float C =
            //   (segmentEnd.x * segmentStart.y) - (segmentStart.x * segmentEnd.y);
            // const float dist2line = std::fabs((A * point.x) + (B * point.y) + C) /
            //                         std::sqrt((A * A) + (B * B));
            const data::Vector2D vecR {endPoint - startPoint};
            const float distR = endPoint.distance(startPoint);
            const data::Vector2D vecP {poi - startPoint};
            const float dist2line {(vecR.cross(vecP)) / distR};

            if ((closestSegmentIdx < 0) ||
                (closestSegmentIdx >= 0 && (dist2line < closestSegmentLateral))) {
                closestSegmentIdx          = i;
                closestSegmentLongitudinal = vecR.dot(vecP) / distR;
                closestSegmentLateral      = dist2line;
            } else {
                // No need to update
            }
        } else {
            // do nothing
        }
    }

    // Check the vertex of polyline
    std::uint32_t closestVertexIdx {0U};
    float closestVertexDist {poi.distance(polyline[0U])};
    // Find the closest vertex
    for (std::size_t i {1U}; i < polyline.length(); ++i) {
        const float dist2Vertex = poi.distance(polyline[i]);
        if (dist2Vertex < closestVertexDist) {
            closestVertexIdx  = i;
            closestVertexDist = dist2Vertex;
        }
    }

    if ((closestSegmentIdx < 0) || (closestVertexDist < closestSegmentLateral)) {
        // closest distance on vertex
        if (closestVertexIdx == (polyline.length() - 1U)) {    // end point, need special handle
            const data::Position2D& startPoint {polyline[closestVertexIdx - 1U]};
            const data::Position2D& endPoint {polyline[closestVertexIdx]};

            const data::Vector2D vecR {endPoint - startPoint};
            const float distR = endPoint.distance(startPoint);
            const data::Vector2D vecP {poi - endPoint};

            closestSegmentIdx          = closestVertexIdx;
            closestSegmentLongitudinal = vecR.dot(vecP) / distR;
            closestSegmentLateral      = vecR.cross(vecP) / distR;
        } else {
            const data::Position2D& startPoint {polyline[closestVertexIdx]};
            const data::Position2D& endPoint {polyline[closestVertexIdx + 1U]};

            const data::Vector2D vecR {endPoint - startPoint};
            const float distR = endPoint.distance(startPoint);
            const data::Vector2D vecP {poi - startPoint};

            closestSegmentIdx          = closestVertexIdx;
            closestSegmentLongitudinal = vecR.dot(vecP) / distR;
            closestSegmentLateral      = vecR.cross(vecP) / distR;
        }
    } else {
        // do nothing, distance already calculated
    }

    // closest distance on segment
    result.polylineIdx        = closestSegmentIdx;
    result.longitudinalOffset = closestSegmentLongitudinal;
    result.lateralDistance    = closestSegmentLateral;

    return result;
}

}    // namespace frenet
}    // namespace intent
}    // namespace cooboc

#endif
