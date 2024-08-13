#include "intents/trajectory_intent/trajectory_intent.h"
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {

namespace detail {
float calculateApproximateRouteLength() {
    if (routeTopic.polylineLength < 2) {
        return 0.0F;
    }

    float totalLength {0.0F};
    for (std::size_t i {1U}; i < routeTopic.polylineLength; ++i) {
        const data::Position2D &startPoint {routeTopic.polyline[i - 1U]};
        const data::Position2D &endPoint {routeTopic.polyline[i]};
        totalLength += startPoint.distance(endPoint);
    }
    return totalLength;
}
}    // namespace detail

TrajectoryIntent::TrajectoryIntent() {}
TrajectoryIntent::~TrajectoryIntent() {}
void TrajectoryIntent::setup() {}

// TrajectoryIntent reads the RouteTopic and output a runnable trajectory
void TrajectoryIntent::tick() {
    float routeTotalLength = detail::calculateApproximateRouteLength();
}

}    // namespace intent
}    // namespace cooboc