#include "intents/reference_path_intent/components/vertex_property.h"
#include <cstdint>
#include <cstdio>
#include <vector>
#include "intents/topics/route_topic.h"
#include "utils/math.h"


namespace cooboc {
namespace intent {
namespace reference_path {


void updateRouteProfile(const RouteTopic &routeTopic, RouteProfile &routeProfile) {
    const std::size_t totalVertexNumber {routeTopic.polyline.length()};
    if (totalVertexNumber < 2U) {
        return;
    }
    std::vector<data::Position2D> previousControlPoints;
    const data::Position2D &firstPoint {routeTopic.polyline[0U]};
    previousControlPoints.push_back(firstPoint);
    const data::CurvatureDistribution firstVertexProperty {routeTopic.connectivityProperties[0U]};
    data::Vector2D previousSegment {routeTopic.polyline[1U] - routeTopic.polyline[0U]};
    // data::PolarVector2D previousPolar {utils::math::to<data::PolarVector2D>(previousSegment)};
    data::Vector2D previousNormalizedVector {utils::math::normalize(previousSegment)};
    float previousSegmentLength {previousSegment.abs()};

    switch (firstVertexProperty) {
        case (data::CurvatureDistribution::CONSIDER_PREVIOUS): {
            std::fprintf(stderr, "Invalid curvature property at route first vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::CONSIDER_NEXT): {
            previousControlPoints.push_back(
              {firstPoint.x + (detail::kBezierSmoothRatio * previousSegment.x),
               firstPoint.y + (detail::kBezierSmoothRatio * previousSegment.y)});

            break;
        }
        case (data::CurvatureDistribution::CONSIDER_BOTH): {
            std::fprintf(stderr, "Invalid curvature property at route first vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::CONSTANT_NEXT): {
            std::fprintf(stderr, "Invalid curvature property at route first vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::DONT_CARE): {
            break;
        }
        default: {
            std::fprintf(stderr, "program should not go here\r\n");
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    // process all vertexes in the middle of route
    for (std::size_t i {1U}; i < (totalVertexNumber - 1U); ++i) {
        std::vector<data::Position2D> nextControlPoints;
        const data::Position2D &currentVertex {routeTopic.polyline[i]};
        nextControlPoints.push_back(currentVertex);
        const data::CurvatureDistribution &vertexProperty {routeTopic.connectivityProperties[i]};
        const data::Vector2D nextSegment {routeTopic.polyline[i + 1U] - routeTopic.polyline[i]};
        // const data::PolarVector2D nextPolar {utils::math::to<data::PolarVector2D>(nextSegment)};
        const data::Vector2D nextNormalizedVector {utils::math::normalize(nextSegment)};
        const float nextSegmentLength {nextSegment.abs()};

        switch (vertexProperty) {
            case (data::CurvatureDistribution::CONSIDER_PREVIOUS): {
                previousControlPoints.push_back(
                  {currentVertex.x - (detail::kBezierSmoothRatio * previousSegment.x),
                   currentVertex.y - (detail::kBezierSmoothRatio * previousSegment.y)});
                nextControlPoints.push_back(
                  {currentVertex.x +
                     (detail::kBezierSmoothRatio * previousNormalizedVector.x * nextSegmentLength),
                   currentVertex.y + (detail::kBezierSmoothRatio * previousNormalizedVector.y *
                                      nextSegmentLength)});

                break;
            }
            case (data::CurvatureDistribution::CONSIDER_NEXT): {
                previousControlPoints.push_back(
                  {currentVertex.x -
                     (detail::kBezierSmoothRatio * nextNormalizedVector.x * previousSegmentLength),
                   currentVertex.y - (detail::kBezierSmoothRatio * nextNormalizedVector.y *
                                      previousSegmentLength)});
                nextControlPoints.push_back(
                  {currentVertex.x + (detail::kBezierSmoothRatio * nextSegment.x),
                   currentVertex.y + (detail::kBezierSmoothRatio * nextSegment.y)});
                break;
            }
            case (data::CurvatureDistribution::CONSIDER_BOTH): {
                const data::Vector2D middleVector =
                  (previousNormalizedVector + nextNormalizedVector) / 2.0F;

                if (!utils::math::equals(middleVector, {0.0F, 0.0F})) {
                    const float middleVectorLength = middleVector.abs();

                    previousControlPoints.push_back(
                      {currentVertex.x - (detail::kBezierSmoothRatio * middleVector.x *
                                          previousSegmentLength / middleVectorLength),
                       currentVertex.y - (detail::kBezierSmoothRatio * middleVector.y *
                                          previousSegmentLength / middleVectorLength)});

                    nextControlPoints.push_back(
                      {currentVertex.x + (detail::kBezierSmoothRatio * middleVector.x *
                                          previousSegmentLength / middleVectorLength),
                       currentVertex.y + (detail::kBezierSmoothRatio * middleVector.y *
                                          previousSegmentLength / middleVectorLength)});
                } else {
                    // do nothing, ignore this point
                }
                break;
            }
            case (data::CurvatureDistribution::CONSTANT_NEXT): {
                // TODO: Not implemented
                std::fprintf(stderr, "Not Implemented, ignore it\r\n");
                // previousControlPoints.push_back(
                //   {currentVertex.x -
                //      (detail::kBezierSmoothRatio * nextNormalizedVector.x *
                //      previousSegmentLength),
                //    currentVertex.y - (detail::kBezierSmoothRatio * nextNormalizedVector.y *
                //                       previousSegmentLength)});

                // nextControlPoints.push_back(
                //   {currentVertex.x + (detail::kBezierSmoothRatio * nextSegment.x),
                //    currentVertex.y + (detail::kBezierSmoothRatio * nextSegment.y)});

                break;
            }
            case (data::CurvatureDistribution::DONT_CARE): {
                break;
            }
            default: {
                std::fprintf(stderr, "program should not go here\r\n");
                break;
            }
        }


        previousControlPoints.push_back(currentVertex);
        routeProfile[i - 1U]  = previousControlPoints;
        previousControlPoints = nextControlPoints;
        previousSegment       = nextSegment;
        // previousPolar         = nextPolar;
        previousNormalizedVector = nextNormalizedVector;
        previousSegmentLength    = nextSegmentLength;
    }

    ////////////////////////////////////////////////////////////////////
    // Put last segment

    const data::Position2D lastVertex {routeTopic.polyline.back()};
    const data::CurvatureDistribution &lastVertexProperty {
      routeTopic.connectivityProperties[totalVertexNumber - 1U]};
    const data::Vector2D &lastSegment {previousSegment};
    std::vector<data::Position2D> &lastControlPoints {previousControlPoints};


    // ///
    // data::Vector2D previousSegment {routeTopic.polyline[1U] - routeTopic.polyline[0U]};
    // // data::PolarVector2D previousPolar
    // {utils::math::to<data::PolarVector2D>(previousSegment)}; data::Vector2D
    // previousNormalizedVector {utils::math::normalize(previousSegment)}; float
    // previousSegmentLength {previousSegment.abs()};

    switch (lastVertexProperty) {
        case (data::CurvatureDistribution::CONSIDER_PREVIOUS): {
            lastControlPoints.push_back(
              {lastVertex.x - (detail::kBezierSmoothRatio * lastSegment.x),
               lastVertex.y - (detail::kBezierSmoothRatio * lastSegment.y)});
            break;
        }
        case (data::CurvatureDistribution::CONSIDER_NEXT): {
            std::fprintf(stderr, "Invalid curvature property at route last vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::CONSIDER_BOTH): {
            std::fprintf(stderr, "Invalid curvature property at route last vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::CONSTANT_NEXT): {
            std::fprintf(stderr, "Invalid curvature property at route last vertex, ignore it\r\n");
            break;
        }
        case (data::CurvatureDistribution::DONT_CARE): {
            break;
        }
        default: {
            std::fprintf(stderr, "program should not go here\r\n");
            break;
        }
    }
    lastControlPoints.push_back(lastVertex);
    routeProfile[routeTopic.polyline.length() - 2U] = lastControlPoints;
}


}    // namespace reference_path
}    // namespace intent
}    // namespace cooboc