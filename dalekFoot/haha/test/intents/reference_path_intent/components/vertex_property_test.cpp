#include "intents/reference_path_intent/components/vertex_property.h"
#include "intents/topics/route_topic.h"
#include "test/utest.h"

UTEST(ReferencePathIntentTest, EmptyRouteTest) {
    // Setup
    cooboc::intent::RouteTopic routeTopic {};
    cooboc::intent::reference_path::RouteProfile routeProfile {};

    // Run
    cooboc::intent::reference_path::updateRouteProfile(routeTopic, routeProfile);

    // Test
    // Should output nothing
    EXPECT_EQ(routeProfile[0U].size(), 0U);
}


UTEST(ReferencePathIntentTest, TwoPointsTest) {
    // Setup
    cooboc::intent::RouteTopic routeTopic {};
    cooboc::intent::reference_path::RouteProfile routeProfile {};
    routeTopic.polyline.push_back({0.0F, 0.0F});
    routeTopic.polyline.push_back({1.0F, 0.0F});
    routeTopic.connectivityProperties[0U] = cooboc::data::CurvatureDistribution::CONSIDER_PREVIOUS;
    routeTopic.connectivityProperties[1U] = cooboc::data::CurvatureDistribution::CONSIDER_PREVIOUS;

    // Run
    cooboc::intent::reference_path::updateRouteProfile(routeTopic, routeProfile);

    // Test
    // Should output nothing
    EXPECT_EQ(routeProfile[0U].size(), 3U);
    EXPECT_EQ(routeProfile[1U].size(), 0U);
}
