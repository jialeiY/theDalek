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

UTEST(ReferencePathIntentTest, EndpointTest) {
    using CD                       = cooboc::data::CurvatureDistribution;
    constexpr float nearPointValue = cooboc::intent::reference_path::detail::kBezierSmoothRatio;
    constexpr float farPointValue =
      1.0F - cooboc::intent::reference_path::detail::kBezierSmoothRatio;

    std::vector<std::tuple<CD, CD, std::size_t, float>> parameterList {
      {CD::CONSIDER_PREVIOUS, CD::CONSIDER_PREVIOUS, 3U, farPointValue},
      {CD::CONSIDER_PREVIOUS, CD::CONSIDER_NEXT, 2U, 1.0F},
      {CD::CONSIDER_PREVIOUS, CD::CONSIDER_BOTH, 2U, 1.0F},
      {CD::CONSIDER_PREVIOUS, CD::CONSTANT_NEXT, 2U, 1.0F},
      {CD::CONSIDER_PREVIOUS, CD::DONT_CARE, 2U, 1.0F},

      {CD::CONSIDER_NEXT, CD::CONSIDER_PREVIOUS, 4U, nearPointValue},
      {CD::CONSIDER_NEXT, CD::CONSIDER_NEXT, 3U, nearPointValue},
      {CD::CONSIDER_NEXT, CD::CONSIDER_BOTH, 3U, nearPointValue},
      {CD::CONSIDER_NEXT, CD::CONSTANT_NEXT, 3U, nearPointValue},
      {CD::CONSIDER_NEXT, CD::DONT_CARE, 3U, nearPointValue},

      {CD::CONSIDER_BOTH, CD::CONSIDER_PREVIOUS, 3U, farPointValue},
      {CD::CONSIDER_BOTH, CD::CONSIDER_NEXT, 2U, 1.0F},
      {CD::CONSIDER_BOTH, CD::CONSIDER_BOTH, 2U, 1.0F},
      {CD::CONSIDER_BOTH, CD::CONSTANT_NEXT, 2U, 1.0F},
      {CD::CONSIDER_BOTH, CD::DONT_CARE, 2U, 1.0F},

      {CD::CONSTANT_NEXT, CD::CONSIDER_PREVIOUS, 3U, farPointValue},
      {CD::CONSTANT_NEXT, CD::CONSIDER_NEXT, 2U, 1.0F},
      {CD::CONSTANT_NEXT, CD::CONSIDER_BOTH, 2U, 1.0F},
      {CD::CONSTANT_NEXT, CD::CONSTANT_NEXT, 2U, 1.0F},
      {CD::CONSTANT_NEXT, CD::DONT_CARE, 2U, 1.0F},

      {CD::DONT_CARE, CD::CONSIDER_PREVIOUS, 3U, farPointValue},
      {CD::DONT_CARE, CD::CONSIDER_NEXT, 2U, 1.0F},
      {CD::DONT_CARE, CD::CONSIDER_BOTH, 2U, 1.0F},
      {CD::DONT_CARE, CD::CONSTANT_NEXT, 2U, 1.0F},
      {CD::DONT_CARE, CD::DONT_CARE, 2U, 1.0F},
    };


    for (const auto &item : parameterList) {
        // Setup
        const CD firstProperty                      = std::get<0>(item);
        const CD LastProperty                       = std::get<1>(item);
        const std::size_t expectControlPointsNumber = std::get<2>(item);
        const float expectMiddlePointPosition       = std::get<3>(item);

        cooboc::intent::RouteTopic routeTopic {};
        cooboc::intent::reference_path::RouteProfile routeProfile {};
        routeTopic.polyline.push_back({0.0F, 0.0F});
        routeTopic.polyline.push_back({1.0F, 0.0F});
        routeTopic.connectivityProperties[0U] = firstProperty;
        routeTopic.connectivityProperties[1U] = LastProperty;

        // Run
        cooboc::intent::reference_path::updateRouteProfile(routeTopic, routeProfile);

        // Test
        // Should output nothing

        ASSERT_EQ(routeProfile[0U].size(), expectControlPointsNumber);
        EXPECT_EQ(routeProfile[1U].size(), 0U);
        EXPECT_NEAR(routeProfile[0U][0U].x, 0.0F, 1e-6);
        EXPECT_NEAR(routeProfile[0U][0U].y, 0.0F, 1e-6);
        EXPECT_NEAR(routeProfile[0U][expectControlPointsNumber - 1U].x, 1.0F, 1e-6);
        EXPECT_NEAR(routeProfile[0U][expectControlPointsNumber - 1U].y, 0.0F, 1e-6);

        EXPECT_NEAR(routeProfile[0U][1].x, expectMiddlePointPosition, 1e-6);
        EXPECT_NEAR(routeProfile[0U][1].y, 0.0F, 1e-6);
    }
}


UTEST(ReferencePathIntentTest, MiddlePointTest) {
    using CD = cooboc::data::CurvatureDistribution;
    cooboc::intent::RouteTopic routeTopic {};
    cooboc::intent::reference_path::RouteProfile routeProfile {};
    routeTopic.polyline.push_back({0.0F, 0.0F});
    routeTopic.polyline.push_back({1.0F, 0.0F});
    routeTopic.polyline.push_back({2.0F, 0.0F});

    routeTopic.connectivityProperties[0U] = CD::DONT_CARE;
    routeTopic.connectivityProperties[2U] = CD::DONT_CARE;


    std::vector<std::tuple<CD, std::size_t, std::size_t>> parameterList {
      {CD::CONSIDER_PREVIOUS, 3U, 2U},
      {CD::CONSIDER_NEXT, 2U, 3U},
      {CD::CONSIDER_BOTH, 3U, 3U},
      {CD::CONSTANT_NEXT, 2U, 2U},
      {CD::DONT_CARE, 2U, 2U},

    };

    for (const auto &item : parameterList) {
        routeTopic.connectivityProperties[1U] = std::get<0>(item);
        const std::size_t expectFirstSegmentControlPointsNumber {std::get<1U>(item)};
        const std::size_t expectSecondSegmentControlPointsNumber {std::get<2U>(item)};

        // Run
        cooboc::intent::reference_path::updateRouteProfile(routeTopic, routeProfile);

        // Test
        // Should output nothing
        EXPECT_EQ(routeProfile[0U].size(), expectFirstSegmentControlPointsNumber);
        EXPECT_EQ_MSG(routeProfile[1U].size(),
                      expectSecondSegmentControlPointsNumber,
                      cooboc::data::toString(routeTopic.connectivityProperties[1U]));
        EXPECT_EQ(routeProfile[2U].size(), 0U);
    }


    // EXPECT_NEAR(routeProfile[0U][0U].x, 0.0F, 1e-6);
    // EXPECT_NEAR(routeProfile[0U][0U].y, 0.0F, 1e-6);
    // EXPECT_NEAR(routeProfile[0U][expectControlPointsNumber - 1U].x, 1.0F, 1e-6);
    // EXPECT_NEAR(routeProfile[0U][expectControlPointsNumber - 1U].y, 0.0F, 1e-6);

    // EXPECT_NEAR(routeProfile[0U][1].x, expectMiddlePointPosition, 1e-6);
    // EXPECT_NEAR(routeProfile[0U][1].y, 0.0F, 1e-6);
}
