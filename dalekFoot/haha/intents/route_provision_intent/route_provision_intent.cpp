#include "intents/route_provision_intent/route_provision_intent.h"
#include <cstdint>
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {
RouteProvisionIntent::RouteProvisionIntent() : uniqueRouteId_ {0U} {}
RouteProvisionIntent::~RouteProvisionIntent() {}

void RouteProvisionIntent::setup() {
    routeTopic.hasValue       = false;
    routeTopic.routeId        = uniqueRouteId_;
    routeTopic.polylineLength = 0U;
    for (std::size_t i {0U}; i < RouteTopic::kPolylineLength; ++i) {
        routeTopic.polyline[i] = data::Position2D {0.0F, 0.0F};
    }
}

void RouteProvisionIntent::tick() {
    routeTopic.hasValue       = true;
    routeTopic.routeId        = uniqueRouteId_;
    routeTopic.polylineLength = 3U;
    routeTopic.polyline[0]    = data::Position2D {0.0F, 0.0F};
    routeTopic.polyline[1]    = data::Position2D {1.0F, 0.0F};
    routeTopic.polyline[2]    = data::Position2D {1.2F, 0.1F};
}

}    // namespace intent
}    // namespace cooboc