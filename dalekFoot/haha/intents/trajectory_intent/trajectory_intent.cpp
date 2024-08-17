#include "intents/trajectory_intent/trajectory_intent.h"
#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>
#include "intents/topics/route_topic.h"
#include "intents/topics/topics.h"
namespace cooboc {
namespace intent {

namespace detail {


float calculateApproximateRouteLength(RouteSegmentLengthArray &routeSegmentLengthArray) {
    if (routeTopic.polylineLength < 2) {
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

void makeTrajectory(const data::Position2D &startPoint,
                    const std::optional<float> &startPointOrientationOpt,
                    const data::Position2D &endPoint,
                    const data::CurvatureDistribution &curvatureDistribution,
                    const std::size_t maximumPointNumber,
                    PassingPointList &passingPointList);

void generateTrajectoriesBasedOnRoutes(const RouteTopic &routeTopic,
                                       TrajectoryTopic &trajectoryTopic) {
    trajectoryTopic.hasValue     = true;
    trajectoryTopic.trajectoryId = generateTrajectoryId();

    // start point
    trajectoryTopic.passingPointSize         = 1U;
    trajectoryTopic.passingPoint[0].position = routeTopic.startPoint;

    std::optional<float> startPointOrientationOpt {};
    PassingPointList passingPointList;
    PassingPoint makeTrajectory(routeTopic.startPoint,
                                startPointOrientationOpt,
                                routeTopic.routeSegment[0].endPoint,
                                routeTopic.routeSegment[0].curvatureDistribution,
                                30U,
                                passingPointList);


}    // namespace detail

TrajectoryIntent::TrajectoryIntent() {}
TrajectoryIntent::~TrajectoryIntent() {}
void TrajectoryIntent::setup() {
    trajectoryTopic.hasValue         = false;
    trajectoryTopic.passingPointSize = 0U;
    for (std::size_t i {0U}; i < TrajectoryTopic::kPassingPointCapacity; ++i) {
        PassingPoint &passingPoint {trajectoryTopic.passingPoint[i]};
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
        detail::generateTrajectoiesBasedOnRoutes(routeTopic, trajectoryTopic);
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