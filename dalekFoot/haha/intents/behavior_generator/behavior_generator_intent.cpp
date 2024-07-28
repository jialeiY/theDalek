#include "intents/behavior_generator/behavior_generator_intent.h"
#include <cmath>
#include <cstdint>
#include "data/defs/position2d.h"
#include "data/defs/vector2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

BehaviorGeneratorIntent::BehaviorGeneratorIntent() {}

BehaviorGeneratorIntent::~BehaviorGeneratorIntent() {}

void BehaviorGeneratorIntent::setup() {
    planningRequestTopic.fromPosition   = data::Position2D {0.0F, 0.0F};
    planningRequestTopic.targetPosition = data::Position2D {0.0F, 0.0F};
    planningRequestTopic.targetVelocity = data::Vector2D {0.0F, 0.0F};
}

void BehaviorGeneratorIntent::tick() {
    // cycle = 1S
    std::uint64_t milli {utils::time::milliseconds()};
    milli %= 1000ULL;

    float x =
      std::cos(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);
    float y =
      std::sin(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);

    planningRequestTopic.targetPosition.x = 0.500F * x;
    planningRequestTopic.targetPosition.y = 0.500F * y;


    std::uint64_t fromm = utils::time::milliseconds();
    fromm *= 3.27;
    fromm %= 373;

    float ix =
      std::cos(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    float iy =
      std::sin(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    planningRequestTopic.fromPosition.x = 0.08 * ix;
    planningRequestTopic.fromPosition.y = 0.12 * iy;
}

}    // namespace intent
}    // namespace cooboc