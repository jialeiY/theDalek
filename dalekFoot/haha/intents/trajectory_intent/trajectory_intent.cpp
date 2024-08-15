#include "intents/trajectory_intent/trajectory_intent.h"
#include <array>
#include <iostream>
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

}    // namespace detail

TrajectoryIntent::TrajectoryIntent() {}
TrajectoryIntent::~TrajectoryIntent() {}
void TrajectoryIntent::setup() {}

// TrajectoryIntent reads the RouteTopic and output a runnable trajectory
void TrajectoryIntent::tick() {
    std::array<float, RouteTopic::kPolylineCapacity> routeSegmentLength;
    float routeTotalLength = detail::calculateApproximateRouteLength(routeSegmentLength);
    std::cout << "the length: " << routeTotalLength << std::endl;

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