#include "intents/trajectory_intent/trajectory/trajectory.h"
#include <optional>
#include <string>
#include <vector>
#include "data/defs/polar_vector2d.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
namespace trajectory {


void generatePassingPointListBasedOnRoute(const data::Position2D &startPoint_,
                                          const data::RouteSegment *routeSegment,
                                          const std::size_t routeSegmentSize,
                                          PassingPointList &passingPointList) {
    // Initialize the loop
    data::Position2D startPoint = startPoint_;
    std::optional<float> startPointOrientationOpt {};
    std::optional<float> currentSegmentStartOrientationOpt {};
    std::optional<float> nextSegmentOrientationOpt {};

    // Put the starting point into the result
    passingPointList.push_back(startPoint);

    for (std::size_t i {0U}; i < routeSegmentSize; ++i) {
        const data::Position2D &currentSegmentEndpoint {routeSegment[i].endPoint};
        // TODO: calculate the suggestMaximumPassingPointNumber based on the length of the route
        const std::size_t suggestMaximumPassingPointNumber {30U};

        if ((i + 1U) < routeSegmentSize) {
            // Not the last route
            const data::Position2D &nextSegmentEndpoint {routeSegment[i + 1U].endPoint};
            nextSegmentOrientationOpt =
              utils::math::to<data::PolarVector2D>(nextSegmentEndpoint - currentSegmentEndpoint)
                .orientation;
        } else {
            // The last route
            nextSegmentOrientationOpt.reset();
        }
        startPointOrientationOpt = detail::makePassingPoints(startPoint,
                                                             startPointOrientationOpt,
                                                             currentSegmentEndpoint,
                                                             nextSegmentOrientationOpt,
                                                             routeSegment[i].curvatureDistribution,
                                                             suggestMaximumPassingPointNumber,
                                                             passingPointList);

        startPoint = currentSegmentEndpoint;
    }
}

namespace detail {

constexpr static float kBezierSmoothRatio {0.3F};


// float calculateApproximateRouteLength(const RouteTopic &routeTopic,
//                                       RouteSegmentLengthArray &routeSegmentLengthArray) {
//     if (routeTopic.routeSegmentSize < 2) {
//         return 0.0F;
//     }

//     float totalLength {0.0F};
//     // for (std::size_t i {0U}; i < routeTopic.polylineLength - 1U; ++i) {
//     //     const data::Position2D &startPoint {routeTopic.polyline[i]};
//     //     const data::Position2D &endPoint {routeTopic.polyline[i + 1U]};
//     //     const float dist {startPoint.distance(endPoint)};
//     //     routeSegmentLengthArray.at(i) = dist;
//     //     totalLength += dist;
//     // }
//     return totalLength;
// }


std::optional<float> makePassingPoints(const data::Position2D &startPoint,
                                       const std::optional<float> &startPointOrientationOpt,
                                       const data::Position2D &endPoint,
                                       std::optional<float> &nextSegmentOrientationOpt,
                                       const data::CurvatureDistribution &curvatureDistribution,
                                       const std::size_t maximumPointNumber,
                                       PassingPointList &passingPointList) {
    std::optional<float> lastOrientationOpt {};

    if (maximumPointNumber < 1U) {
        throw std::string("the maximumPointNumber should not less than 1");
        return lastOrientationOpt;
    }

    // TODO: if only one point, just add end point

    const float segmentLength = startPoint.distance(endPoint);

    std::vector<data::Position2D> controlPoints {};
    controlPoints.push_back(startPoint);
    if (startPointOrientationOpt.has_value()) {
        controlPoints.push_back(startPoint +
                                data::PolarVector2D {startPointOrientationOpt.value(),
                                                     segmentLength * kBezierSmoothRatio});
    }

    switch (curvatureDistribution) {
        case (data::CurvatureDistribution::CONSIDER_CURRENT): {
            const data::Vector2D currentVec = endPoint - startPoint;
            controlPoints.push_back(
              endPoint -
              data::PolarVector2D {utils::math::to<data::PolarVector2D>(currentVec).orientation,
                                   segmentLength * kBezierSmoothRatio});
            controlPoints.push_back(endPoint);
            break;
        }
        case (data::CurvatureDistribution::CONSIDER_NEXT): {
            if (nextSegmentOrientationOpt.has_value()) {
                controlPoints.push_back(endPoint -
                                        data::PolarVector2D {nextSegmentOrientationOpt.value(),
                                                             segmentLength * kBezierSmoothRatio});
            }
            controlPoints.push_back(endPoint);
            break;
        }
        case (data::CurvatureDistribution::CONSIDER_BOTH): {
            const data::Vector2D predecessorVec = endPoint - startPoint;
            float orientation = utils::math::to<data::PolarVector2D>(predecessorVec).orientation;
            if (nextSegmentOrientationOpt.has_value()) {
                orientation = (orientation + nextSegmentOrientationOpt.value()) / 2.0F;
            }
            controlPoints.push_back(
              endPoint - data::PolarVector2D {orientation, segmentLength * kBezierSmoothRatio});
            controlPoints.push_back(endPoint);
            break;
        }
        default: {
            std::fprintf(stderr, "CurvatureDistribution not implemented yet\r\n");
            controlPoints.push_back(endPoint);
            break;
        }
    }

    // printf("size: %ld\r\n", controlPoints.size());
    switch (controlPoints.size()) {
        case (2U): {
            std::fprintf(stderr, "direct line not implemented yet\r\n");
            break;
        }
        case (3U): {
            makeCubicBezierCurve(controlPoints[0U],
                                 controlPoints[1U],
                                 controlPoints[2U],
                                 maximumPointNumber - 1U,
                                 passingPointList);
            const data::Position2D &lastPoint = passingPointList.back();
            passingPointList.push_back(endPoint);

            if (utils::math::equals(endPoint, lastPoint)) {
                // TODO
                throw std::string("could not determine the last orientation");
            }
            lastOrientationOpt =
              utils::math::to<data::PolarVector2D>(endPoint - lastPoint).orientation;
            break;
        }
        case (4U): {
            // quadratic
            makeQuadraticBezierCurve(controlPoints[0U],
                                     controlPoints[1U],
                                     controlPoints[2U],
                                     controlPoints[3U],
                                     maximumPointNumber - 1U,
                                     passingPointList);
            const data::Position2D &lastPoint = passingPointList.back();
            passingPointList.push_back(endPoint);

            if (utils::math::equals(endPoint, lastPoint)) {
                // TODO
                throw std::string("could not determine the last orientation");
            }
            lastOrientationOpt =
              utils::math::to<data::PolarVector2D>(endPoint - lastPoint).orientation;
            break;
        }
        default: {
            std::fprintf(stderr, "invalid curve define\r\n");
            // TODO: add error log
            break;
        }
    }

    if ((curvatureDistribution == data::CurvatureDistribution::CONSIDER_NEXT) &&
        (nextSegmentOrientationOpt.has_value())) {
        lastOrientationOpt = nextSegmentOrientationOpt;
    }


    return lastOrientationOpt;
}


void makeCubicBezierCurve(const data::Position2D &pa,
                          const data::Position2D &pb,
                          const data::Position2D &pc,
                          const std::size_t count,
                          PassingPointList &passingPointList) {
    const float percent = 1.0F / (count + 1U);
    float sampleValue   = percent;
    for (std::size_t i {0U}; i < count; ++i) {
        const data::Position2D ia = utils::math::interpolate(pa, pb, sampleValue);
        const data::Position2D ib = utils::math::interpolate(pb, pc, sampleValue);

        const data::Position2D point = utils::math::interpolate(ia, ib, sampleValue);
        passingPointList.push_back(point);
        sampleValue += percent;
    }
}

void makeQuadraticBezierCurve(const data::Position2D &pa,
                              const data::Position2D &pb,
                              const data::Position2D &pc,
                              const data::Position2D &pd,
                              const std::size_t count,
                              PassingPointList &passingPointList) {
    const float percent = 1.0F / (count + 1U);
    float sampleValue   = percent;
    for (std::size_t i {0U}; i < count; ++i) {
        const data::Position2D pab = utils::math::interpolate(pa, pb, sampleValue);
        const data::Position2D pbc = utils::math::interpolate(pb, pc, sampleValue);
        const data::Position2D pcd = utils::math::interpolate(pc, pd, sampleValue);

        const data::Position2D pabc = utils::math::interpolate(pab, pbc, sampleValue);
        const data::Position2D pbcd = utils::math::interpolate(pbc, pcd, sampleValue);

        const data::Position2D pabcd = utils::math::interpolate(pabc, pbcd, sampleValue);

        passingPointList.push_back(pabcd);
        sampleValue += percent;
    }
}


}    // namespace detail
}    // namespace trajectory
}    // namespace intent
}    // namespace cooboc