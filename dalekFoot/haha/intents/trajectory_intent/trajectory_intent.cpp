#include "intents/trajectory_intent/trajectory_intent.h"
#include <array>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <optional>
#include <vector>
#include "data/defs/passing_point.h"
#include "data/defs/polar_vector2d.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/topics.h"
#include "utils/math.h"


namespace cooboc {
namespace intent {

namespace detail {

constexpr float kBezierSmoothRatio {0.3F};

float calculateApproximateRouteLength(RouteSegmentLengthArray &routeSegmentLengthArray) {
    if (routeTopic.routeSegmentSize < 2) {
        return 0.0F;
    }

    float totalLength {0.0F};
    // for (std::size_t i {0U}; i < routeTopic.polylineLength - 1U; ++i) {
    //     const data::Position2D &startPoint {routeTopic.polyline[i]};
    //     const data::Position2D &endPoint {routeTopic.polyline[i + 1U]};
    //     const float dist {startPoint.distance(endPoint)};
    //     routeSegmentLengthArray.at(i) = dist;
    //     totalLength += dist;
    // }
    return totalLength;
}

static TrajectoryId trajectoryId {0U};

TrajectoryId generateTrajectoryId() { return trajectoryId++; }

void generateTrajectoriesBasedOnRoutes(const RouteTopic &routeTopic,
                                       TrajectoryTopic &trajectoryTopic) {
    trajectoryTopic.hasValue     = true;
    trajectoryTopic.trajectoryId = generateTrajectoryId();


    std::optional<float> startPointOrientationOpt {};
    PassingPointList passingPointList;

    // start point
    passingPointList.push_back(data::PassingPoint {routeTopic.startPoint});

    const data::Position2D &currentSegmentEndpoint {routeTopic.routeSegment[0].endPoint};
    std::optional<float> nextSegmentOrientationOpt {};
    if (routeTopic.routeSegmentSize > 1U) {
        const data::Position2D &nextSegmentEndpoint {routeTopic.routeSegment[1U].endPoint};
        nextSegmentOrientationOpt =
          utils::math::to<data::PolarVector2D>(nextSegmentEndpoint - currentSegmentEndpoint)
            .orientation;
    }
    detail::makeTrajectory(routeTopic.startPoint,
                           startPointOrientationOpt,
                           currentSegmentEndpoint,
                           nextSegmentOrientationOpt,
                           routeTopic.routeSegment[0].curvatureDistribution,
                           30U,
                           passingPointList);

    // End point
    passingPointList.push_back(data::PassingPoint {currentSegmentEndpoint});
    trajectoryTopic.passingPointSize =
      std::min(TrajectoryTopic::kPassingPointCapacity, passingPointList.size());

    // Move result into the trajectory topic
    for (std::size_t idx {0U}; idx < trajectoryTopic.passingPointSize; ++idx) {
        trajectoryTopic.passingPoint[idx] = passingPointList[idx];
    }
}


float makeTrajectory(const data::Position2D &startPoint,
                     const std::optional<float> &startPointOrientationOpt,
                     const data::Position2D &endPoint,
                     std::optional<float> &nextSegmentOrientationOpt,
                     const data::CurvatureDistribution &curvatureDistribution,
                     const std::size_t maximumPointNumber,
                     PassingPointList &passingPointList) {
    std::printf(
      "from (%f, %f) -> (%f, %f), %u\r\n",
      startPoint.x,
      startPoint.y,
      endPoint.x,
      endPoint.y,
      static_cast<std::underlying_type<data::CurvatureDistribution>::type>(curvatureDistribution));

    const float segmentLength = startPoint.distance(endPoint);

    std::vector<data::Position2D> controlPoints {};
    controlPoints.push_back(startPoint);
    if (startPointOrientationOpt.has_value()) {
        controlPoints.push_back(startPoint -
                                data::PolarVector2D {startPointOrientationOpt.value(),
                                                     segmentLength * kBezierSmoothRatio});
    }

    switch (curvatureDistribution) {
        case (data::CurvatureDistribution::FOLLOW_PREDECESSOR): {
            controlPoints.push_back(endPoint);
            const data::Vector2D predecessorVec = endPoint - startPoint;
            controlPoints.push_back(
              endPoint +
              data::PolarVector2D {utils::math::to<data::PolarVector2D>(predecessorVec).orientation,
                                   segmentLength * kBezierSmoothRatio});
            break;
        }
        case (data::CurvatureDistribution::FOLLOW_SUCCESSOR): {
            controlPoints.push_back(endPoint);
            if (nextSegmentOrientationOpt.has_value()) {
                controlPoints.push_back(endPoint +
                                        data::PolarVector2D {utils::math::to<data::PolarVector2D>(
                                                               nextSegmentOrientationOpt.value())
                                                               .orientation,
                                                             segmentLength * kBezierSmoothRatio});
            }
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

    printf("size: %ld\r\n", controlPoints.size());
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
            break;
        }
        case (4U): {
            // quadratic
            break;
        }
        default: {
            std::fprintf(stderr, "invalid curve define\r\n");
            // TODO: add error log
            break;
        }
    }


    return 0;
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
        passingPointList.push_back(data::PassingPoint {point});
        sampleValue += percent;
    }
}

}    // namespace detail

TrajectoryIntent::TrajectoryIntent() {}
TrajectoryIntent::~TrajectoryIntent() {}
void TrajectoryIntent::setup() {
    trajectoryTopic.hasValue         = false;
    trajectoryTopic.passingPointSize = 0U;
    for (std::size_t i {0U}; i < TrajectoryTopic::kPassingPointCapacity; ++i) {
        data::PassingPoint &passingPoint {trajectoryTopic.passingPoint[i]};
        passingPoint.position = {0.0F, 0.0F};
    }
    trajectoryTopic.routeId = 0U;
}


// TrajectoryIntent reads the RouteTopic and output a runnable trajectory
void TrajectoryIntent::tick() {
    std::array<float, RouteTopic::kPolylineCapacity> routeSegmentLength;
    float routeTotalLength = detail::calculateApproximateRouteLength(routeSegmentLength);
    std::cout << "the length: " << routeTotalLength << std::endl;

    // TODO, check the data validation

    if (routeTopic.hasValue) {
        detail::generateTrajectoriesBasedOnRoutes(routeTopic, trajectoryTopic);
    } else {
        trajectoryTopic.hasValue = false;
    }
    // put the start point into trajectory


    // Generate segment one by one
    // for (std::size_t i {0U}; i < routeTopic.polylineLength - 1U; ++i) {
    //     std::size_t pointCount {
    //       static_cast<std::size_t>(routeSegmentLength[i] * 1000.0F / routeTotalLength)};


    //     const data::Position2D &startPoint {routeTopic.polyline[i]};
    //     const data::Position2D &endPoint {routeTopic.polyline[i + 1U]};
    //}
}

}    // namespace intent
}    // namespace cooboc