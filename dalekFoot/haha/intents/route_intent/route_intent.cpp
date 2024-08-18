#include "intents/route_intent/route_intent.h"
#include <cstdint>
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {
RouteIntent::RouteIntent() : uniqueRouteId_ {0U} {}
RouteIntent::~RouteIntent() {}

void RouteIntent::setup() {
    routeTopic.hasValue         = false;
    routeTopic.routeId          = uniqueRouteId_;
    routeTopic.routeSegmentSize = 0U;
    routeTopic.startPoint       = data::Position2D {0.0F, 0.0F};

    for (std::size_t i {0U}; i < RouteTopic::kPolylineCapacity; ++i) {
        data::RouteSegment &segment {routeTopic.routeSegment[i]};
        segment.endPoint              = data::Position2D {0.0F, 0.0F};
        segment.curvatureDistribution = data::CurvatureDistribution::DONT_CARE;
    }
}

void RouteIntent::tick() {
    routeTopic.hasValue         = true;
    routeTopic.routeId          = uniqueRouteId_;
    routeTopic.routeSegmentSize = 3U;

    routeTopic.startPoint = data::Position2D {0.0F, 0.0F};
    {
        data::RouteSegment &segment {routeTopic.routeSegment[0U]};
        segment.endPoint              = data::Position2D {1.0F, 0.0F};
        segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    }
    {
        data::RouteSegment &segment {routeTopic.routeSegment[1U]};
        segment.endPoint              = data::Position2D {1.2F, 0.1F};
        segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    }
    {
        data::RouteSegment &segment {routeTopic.routeSegment[2U]};
        segment.endPoint              = data::Position2D {2.0, 0.1F};
        segment.curvatureDistribution = data::CurvatureDistribution::CONSTANT;
    }
}

}    // namespace intent
}    // namespace cooboc