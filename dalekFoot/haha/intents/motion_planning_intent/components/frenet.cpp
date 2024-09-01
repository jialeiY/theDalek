#include "intents/motion_planning_intent/components/frenet.h"
#include <cstdint>
#include <tuple>
#include "data/defs/passing_point.h"
#include "data/defs/pose2d.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
namespace motion_planning {

namespace detail {
float calculateDistanceFromPointToSegment(const data::Position2D &point,
                                          const data::Position2D &segmentStart,
                                          const data::Position2D &segmentEnd,
                                          const bool isStartClosed,
                                          const bool isEndClosed) {
    // Is start equals to end
    if (utils::math::equals(segmentStart, segmentEnd)) {
        return point.distance(segmentStart);
    }

    // is on the start point?
    if (utils::math::equals(point.x, segmentStart.x) &&
        utils::math::equals(point.y, segmentStart.y)) {
        return 0.0F;
    }

    // is on the end point?
    if ((utils::math::equals(point.x, segmentEnd.x)) &&
        (utils::math::equals(point.y, segmentEnd.y))) {
        return 0.0F;
    }

    // Point out side of start
    if (isStartClosed) {
        if ((point - segmentStart).dot(segmentEnd - segmentStart) < 0.0F) {
            return point.distance(segmentStart);
        }
    }

    // Point out side of end
    if (isEndClosed) {
        if ((point - segmentEnd).dot(segmentStart - segmentEnd) < 0.0F) {
            return point.distance(segmentEnd);
        }
    }

    // // the representation of line is Ax + By + C = 0;
    // // d = |Ax + Ｂy + C| / sqrt(A^2 + B^2)
    // const float A = (segmentEnd.y - segmentStart.y);
    // const float B = (segmentStart.x - segmentEnd.x);
    // const float C =
    //   (segmentEnd.x * segmentStart.y) - (segmentStart.x * segmentEnd.y);
    // const float dist2line = std::fabs((A * point.x) + (B * point.y) + C) /
    //                         std::sqrt((A * A) + (B * B));
    const float dist2line =
      ((segmentEnd - segmentStart).cross(point - segmentStart)) / segmentStart.distance(segmentEnd);
    return dist2line;
}
}    // namespace detail

std::tuple<std::size_t, float> calculatePoseInFrenet(const data::Pose2D &poseInWorld,
                                                     const data::PassingPoint *passingPoint,
                                                     const std::size_t &passingPointSize,
                                                     data::Pose2D &poseInFrenet) {
    // TODO, assume route always has data now

    // Find the segment
    std::size_t closestSegmentId {0U};
    float closestDistance {std::numeric_limits<float>::max()};

    data::Position2D lastPoint = passingPoint[0U].position;
    for (std::size_t i {1U}; i < passingPointSize; ++i) {
        const bool firstNeedOpen = (i != 1U);    // only the first one need to open?
        float dist               = std::fabs(detail::calculateDistanceFromPointToSegment(
          poseInWorld.position, lastPoint, passingPoint[i].position, firstNeedOpen, true));
        if (dist < closestDistance) {
            closestSegmentId = i - 1;
            closestDistance  = dist;
        }
        lastPoint = passingPoint[i].position;
    }

    // calculate S
    float s = 0.0F;
    // Calculate all s before current segment
    for (std::size_t i {0U}; i < closestSegmentId; ++i) { s += passingPoint[i].segment.value; }
    // Calculate s on current segment
    const data::Position2D &headPoint {passingPoint[closestSegmentId].position};
    const data::Position2D &endPoint {passingPoint[closestSegmentId + 1U].position};

    if (!utils::math::equals(headPoint, endPoint)) {
        const data::Position2D veca = endPoint - headPoint;
        const data::Position2D vecb = poseInWorld.position - headPoint;
        s += veca.dot(vecb) / veca.abs();
    } else {
        // TODO
    }

    // Calculate y

    const float y {
      detail::calculateDistanceFromPointToSegment(poseInWorld.position,
                                                  passingPoint[closestSegmentId].position,
                                                  passingPoint[closestSegmentId + 1U].position,
                                                  false,
                                                  false)};

    const data::PolarVector2D &segPolarVec {passingPoint[closestSegmentId + 1U].segment};

    const float orientation =
      utils::math::clampAngle(poseInFrenet.orientation - segPolarVec.orientation);


    poseInFrenet.position    = {s, y};
    poseInFrenet.orientation = orientation;

    return {closestSegmentId, closestDistance};
    // data::Vector2D refSegVec {
    //   (route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId])};
    // data::PolarVector2D refSegPolarVec = utils::math::to<data::PolarVector2D>(refSegVec);
    // return {s, y, refSegPolarVec.orientation};


    // float s = 0.0F;
    // // Calculate all s before current segment
    // for (std::size_t i {0U}; (i + 1U) < closestSegmentId; ++i) {
    //     s += route.polyline[i].distance(route.polyline[i + 1U]);
    // }

    // // Calculate s on current segment
    // if (!utils::math::equals(route.polyline[closestSegmentId],
    //                          route.polyline[closestSegmentId + 1U])) {
    //     const data::Position2D veca =
    //       route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId];
    //     const data::Position2D vecb = odometry.position - route.polyline[closestSegmentId];
    //     s += veca.dot(vecb) / veca.abs();
    // }

    // const float y {calculateDistanceFromPointToSegment(odometry.position,
    //                                                    route.polyline[closestSegmentId],
    //                                                    route.polyline[closestSegmentId + 1U],
    //                                                    false,
    //                                                    false)};

    // data::Vector2D refSegVec {
    //   (route.polyline[closestSegmentId + 1U] - route.polyline[closestSegmentId])};
    // data::PolarVector2D refSegPolarVec = utils::math::to<data::PolarVector2D>(refSegVec);
    // return {s, y, refSegPolarVec.orientation};
}

}    // namespace motion_planning
}    // namespace intent
}    // namespace cooboc