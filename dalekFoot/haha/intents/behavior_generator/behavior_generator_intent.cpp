#include "intents/behavior_generator/behavior_generator_intent.h"
#include <cmath>
#include <cstdint>
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

BehaviorGeneratorIntent::BehaviorGeneratorIntent() {}

BehaviorGeneratorIntent::~BehaviorGeneratorIntent() {}

void BehaviorGeneratorIntent::setup() {
    planningRequestTopic.targetPositionX = 0.500F;
    planningRequestTopic.targetPositionY = 0.500F;
}

void BehaviorGeneratorIntent::tick() {
    // cycle = 1S
    std::uint64_t milli {utils::time::milliseconds()};
    milli %= 1000ULL;
    float x =
      std::cos(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);
    float y =
      std::sin(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);


    planningRequestTopic.targetPositionX = 0.500F * x;
    planningRequestTopic.targetPositionY = 0.500F * y;
}

}    // namespace intent
}    // namespace cooboc