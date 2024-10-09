#include "intents/route_intent/route_intent.h"
#include <cstdint>
#include "intents/topics/topics.h"

namespace cooboc {
namespace intent {
RouteIntent::RouteIntent() : routeTopic_ {} {}
RouteIntent::~RouteIntent() {}

void RouteIntent::setup() {
    routeTopic_.id           = data::kInvalidRouteId;
    routeTopic_.behaviorId   = data::kInvalidBehaviorId;
    routeTopic_.pointsNumber = 0U;


    for (std::size_t i {0U}; i < RouteTopic::kPolylineCapacity; ++i) {
        routeTopic_.points[i]                 = data::Position2D {0.0F, 0.0F};
        routeTopic_.connectivityProperties[i] = data::CurvatureDistribution::DONT_CARE;
    }

    // copy cache to output
    routeTopic = routeTopic_;
}

void RouteIntent::tick() {
    // make a fake route
    if (behaviorTopic.id == data::kInvalidBehaviorId) {
        invalidateOutput();
    } else {
        checkAndMakeRoute(behaviorTopic);
    }
    routeTopic = routeTopic_;


    // routeTopic.hasValue = true;
    // routeTopic.routeId  = uniqueRouteId_;

    // routeTopic.routeSegmentSize = 5U;
    // routeTopic.startPoint = data::Position2D {0.0F, 0.0F};
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[0U]};
    //     segment.endPoint              = data::Position2D {0.3F, 0.0F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[1U]};
    //     segment.endPoint              = data::Position2D {0.7F, 0.3F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[2U]};
    //     segment.endPoint              = data::Position2D {2.0, 0.1F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::FOLLOW_NEXT;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[3U]};
    //     segment.endPoint              = data::Position2D {2.0, -1.1F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::FOLLOW_CURRENT;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[4U]};
    //     segment.endPoint              = data::Position2D {3.0, -0.1F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // routeTopic.routeSegmentSize = 5U;
    // routeTopic.startPoint       = data::Position2D {0.0F, 0.0F};
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[0U]};
    //     segment.endPoint              = data::Position2D {1.0F, 0.0F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[1U]};
    //     segment.endPoint              = data::Position2D {1.0F, 1.0F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[2U]};
    //     segment.endPoint              = data::Position2D {0.0F, 1.0F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::FOLLOW_NEXT;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[3U]};
    //     segment.endPoint              = data::Position2D {0.0F, 0.5F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
    // {
    //     data::RouteSegment &segment {routeTopic.routeSegment[4U]};
    //     segment.endPoint              = data::Position2D {0.0F, 0.0F};
    //     segment.curvatureDistribution = data::CurvatureDistribution::CONSIDER_BOTH;
    // }
}

// bool RouteIntent::needGenerateNewRoute() {
//     // If behaviorTopic has no value, there is no need to generate a new route.
//     // If behaviorTOpic has value, and last route don't have a valid value, need to generate a
//     // new route.
//     // If behaviorTopic has value and last routeOutput have a difference value, a new route is
//     // needed
//     // If behaviorTopic has value and last routeOutput already generated one, no need to generate
//     // again
// }

void RouteIntent::invalidateOutput(void) {
    routeTopic_.id = data::kInvalidRouteId;

    routeTopic_.behaviorId   = data::kInvalidBehaviorId;
    routeTopic_.pointsNumber = 0U;
}

void RouteIntent::checkAndMakeRoute(const intent::BehaviorTopic& behaviorTopic) {
    const bool isLastRouteOutputValid {routeTopic_.id != data::kInvalidRouteId};
    const bool isBehaviorValid {behaviorTopic.id != data::kInvalidBehaviorId};
    const bool isLastRouteOutputDifferent {routeTopic_.behaviorId != behaviorTopic.id};
    if (isLastRouteOutputValid && isBehaviorValid && isLastRouteOutputDifferent) {
        makeRoute(behaviorTopic);
    }
}

void RouteIntent::makeRoute(const intent::BehaviorTopic& behaviorTopic) {
    // Make fake route
    data::Position2D pos {0.0F, 0.0F};
    routeTopic_.id         = makeNewRouteId();
    routeTopic_.behaviorId = behaviorTopic.id;

    constexpr std::size_t kPointsNumber {10U};
    static_assert(kPointsNumber > 2U);
    routeTopic_.pointsNumber = kPointsNumber;
    for (std::size_t i {0U}; i < kPointsNumber; ++i) {
        routeTopic_.points[i] = pos;
        if ((i % 2U) == 0U) {
            pos = pos + data::Vector2D {0.5F, 0.0F};
        } else {
            pos = pos + data::Vector2D {0.0F, 0.5F};
        }
    }
    for (std::size_t i {0U}; i < (kPointsNumber - 2U); ++i) {
        constexpr uint8_t totalCurvatureDistribution {5U};
        routeTopic_.connectivityProperties[i] =
          static_cast<data::CurvatureDistribution>(i % totalCurvatureDistribution);
    }
}

data::RouteId RouteIntent::makeNewRouteId() {
    static data::RouteId genId {data::kInvalidRouteId};
    return ++genId;
}

}    // namespace intent
}    // namespace cooboc