#include "intents/behavior_intent/behavior_intent.h"
#include <cmath>
#include <cstdint>
#include "data/defs/polar_vector2d.h"
#include "data/defs/position2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

BehaviorIntent::BehaviorIntent() {}

BehaviorIntent::~BehaviorIntent() {}

void BehaviorIntent::setup() {
    behaviorTopic.id   = 0U;
    behaviorTopic.task = BehaviorTopic::BehaviorTask::STOP;

    behaviorTopic.moveRequest = {
      .from           = data::Position2D {0.0F, 0.0F},
      .to             = data::Position2D {0.0F, 0.0F},
      .targetVelocity = data::PolarVector2D {0.0F, 0.0F},
    };
}

void BehaviorIntent::tick() {
    const data::Position2D &egoPosition {odometryTopic.pose.position};


    // // cycle = 1S
    // std::uint64_t milli {utils::time::milliseconds()};
    // milli %= 1000ULL;

    // float x = std::cos(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);
    // float y = std::sin(static_cast<float>(milli) * 2.0F * utils::math::PI / 1000.0F);

    // behaviorTopic.targetPosition.x = 0.500F * x;
    // behaviorTopic.targetPosition.y = 0.500F * y;


    // std::uint64_t fromm = utils::time::milliseconds();
    // fromm *= 3.27;
    // fromm %= 373;

    // float ix = std::cos(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    // float iy = std::sin(static_cast<float>(fromm) * 2.0F * utils::math::PI / 373.0F);
    // behaviorTopic.fromPosition.x = 0.08 * ix;
    // behaviorTopic.fromPosition.y = 0.12 * iy;
}

}    // namespace intent
}    // namespace cooboc