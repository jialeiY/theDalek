#include "intents/ego_motion_state_intent/ego_motion_state_intent.h"
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {

constexpr float kAxelLongitudinal {0.25F};
constexpr float kAxelLateral {0.20F};

EgoMotionStateIntent::EgoMotionStateIntent() {}
EgoMotionStateIntent::~EgoMotionStateIntent() {}
void EgoMotionStateIntent::setup() {
    egoMotionStateTopic.velocity            = {0.0F, 0.0F};
    egoMotionStateTopic.acceleration        = {0.0F, 0.0F};
    egoMotionStateTopic.angularVelocity     = 0.0F;
    egoMotionStateTopic.angularAcceleration = 0.0F;
}

void EgoMotionStateIntent::tick() {
    if (!vehicleResponseTopic.isValid) {
        // TODO update ego state using history information
        return;
    }

    const float encoderVx =
      (vehicleResponseTopic.intervalOdometry[0U] + vehicleResponseTopic.intervalOdometry[1U] +
       vehicleResponseTopic.intervalOdometry[2U] + vehicleResponseTopic.intervalOdometry[3U]) /
      4.0F;
    const float encoderVy =
      (vehicleResponseTopic.intervalOdometry[0U] - vehicleResponseTopic.intervalOdometry[1U] +
       vehicleResponseTopic.intervalOdometry[2U] - vehicleResponseTopic.intervalOdometry[3U]) /
      4.0F;
    const float encoderVr =
      (vehicleResponseTopic.intervalOdometry[0U] + vehicleResponseTopic.intervalOdometry[1U] -
       vehicleResponseTopic.intervalOdometry[2U] - vehicleResponseTopic.intervalOdometry[3U]) /
      4.0F;

    const data::Vector2D encoderVelocity {encoderVx, encoderVy};
    const data::Vector2D velocity = encoderVelocity * (utils::math::PI * 0.06F / 4096.0F);
    const float angularVelocity =
      encoderVr *
      (2.0 * utils::math::PI /
       std::sqrt(kAxelLongitudinal * kAxelLongitudinal + kAxelLateral * kAxelLateral)) *
      (utils::math::PI * 0.06F / 4096.0F);

    egoMotionStateTopic.velocity        = utils::math::to<data::PolarVector2D>(velocity);
    egoMotionStateTopic.angularVelocity = angularVelocity;

    // egoMotionStateTopic.velocity.orientation = randomDistribution_(randomGen_) * 3.9F;
    // egoMotionStateTopic.velocity.value       = randomDistribution_(randomGen_) * 3.0 + 0.5;

    // egoMotionStateTopic.acceleration.orientation = randomDistribution_(randomGen_) * 39.4F;
    // egoMotionStateTopic.acceleration.value       = randomDistribution_(randomGen_) * 4.7;
}


}    // namespace intent
}    // namespace cooboc