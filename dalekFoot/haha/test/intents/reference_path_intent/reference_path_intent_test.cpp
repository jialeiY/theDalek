#include "intents/reference_path_intent/reference_path_intent.h"
#include "intents/topics/reference_path_topic.h"
#include "test/utest.h"

class ReferencePathIntentMock : public cooboc::intent::ReferencePathIntent {
  public:
    // Expose everything
    cooboc::intent::ReferencePathTopic &getReferencePathTopicCache() {
        return referencePathTopic_;
    }
    cooboc::intent::reference_path::RouteProfile &getRouteProfile() {
        return routeProfile_;
    }
};

UTEST(ReferencePathIntentTest, SmokeTest) {
    ReferencePathIntentMock referencePathIntent;
    referencePathIntent.setup();
    // Tick with empty data, should not crash
    referencePathIntent.tick();
    // Everything should be reset
    EXPECT_EQ(referencePathIntent.getReferencePathTopicCache().id,
              cooboc::data::kInvalidReferencePathId);
}

UTEST(ReferencePathIntentTest,
      GivenInvalidRouteInput_WhenReferencePathTick_ThenCacheShouldBeReset) {
    // Setup
    ReferencePathIntentMock referencePathIntent;
    referencePathIntent.setup();

    cooboc::intent::RouteTopic routeTopic;
    routeTopic.id = cooboc::data::kInvalidRouteId;
    cooboc::intent::shared::routeTopic = routeTopic;

    // Put a valid id in the cache
    referencePathIntent.getReferencePathTopicCache().id = 34U;    // A valid ID

    // Run
    referencePathIntent.tick();

    // ID should be reset
    EXPECT_EQ(referencePathIntent.getReferencePathTopicCache().id,
              cooboc::data::kInvalidReferencePathId);
}


UTEST(ReferencePathIntentTest, GivenValidRouteInput_WhenReferencePathTick_ThenCacheShouldUpdated) {
    constexpr cooboc::data::RouteId kRouteId = 42U;    // random picked number

    // Setup
    ReferencePathIntentMock referencePathIntent;
    referencePathIntent.setup();

    EXPECT_EQ(referencePathIntent.getReferencePathTopicCache().id,
              cooboc::data::kInvalidReferencePathId);
    EXPECT_EQ(referencePathIntent.getRouteProfile()[0].size(), 0U);

    // Make a valid route input
    cooboc::intent::RouteTopic routeTopic;
    routeTopic.id = kRouteId;
    routeTopic.polyline.push_back({0.0F, 0.0F});
    routeTopic.polyline.push_back({1.0F, 1.0F});
    routeTopic.connectivityProperties[0U] = cooboc::data::CurvatureDistribution::DONT_CARE;
    routeTopic.connectivityProperties[1U] = cooboc::data::CurvatureDistribution::DONT_CARE;

    cooboc::intent::shared::routeTopic = routeTopic;

    // Run
    referencePathIntent.tick();

    // Test
    EXPECT_EQ(referencePathIntent.getReferencePathTopicCache().id, kRouteId);
    EXPECT_GT(referencePathIntent.getRouteProfile()[0].size(), 0U);
}