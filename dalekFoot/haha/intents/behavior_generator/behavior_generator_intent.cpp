#include "intents/behavior_generator/behavior_generator_intent.h"
#include <intents/topics/topics.h>

namespace cooboc {
namespace intent {

BehaviorGeneratorIntent::BehaviorGeneratorIntent() {}

BehaviorGeneratorIntent::~BehaviorGeneratorIntent() {}

void BehaviorGeneratorIntent::setup() {
    planningRequestTopic.targetPositionX = 500.0F;
    planningRequestTopic.targetPositionY = 500.0F;
}

void BehaviorGeneratorIntent::tick() {
    planningRequestTopic.targetPositionX = 500.0F;
    planningRequestTopic.targetPositionY = 500.0F;
}

}    // namespace intent
}    // namespace cooboc