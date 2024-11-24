#include "intents/reference_path_intent/reference_path_intent.h"
#include "intents/topics/reference_path_topic.h"
#include "test/utest.h"

class ReferencePathIntentMock : public cooboc::intent::ReferencePathIntent {
  public:
    // Expose everything
    cooboc::intent::ReferencePathTopic &getReferencePathTopicCache() {
        return referencePathTopic_;
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
    routeTopic.id                      = cooboc::data::kInvalidRouteId;
    cooboc::intent::shared::routeTopic = routeTopic;

    // Put a valid id in the cache
    referencePathIntent.getReferencePathTopicCache().id = 34U;    // A valid ID

    // Run
    referencePathIntent.tick();

    // ID should be reset
    EXPECT_EQ(referencePathIntent.getReferencePathTopicCache().id,
              cooboc::data::kInvalidReferencePathId);
}
