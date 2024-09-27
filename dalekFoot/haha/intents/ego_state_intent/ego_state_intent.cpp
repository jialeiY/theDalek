#include "intents/ego_state_intent/ego_state_intent.h"
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "intents/topics/topics.h"
#include "utils/math.h"

namespace cooboc {
namespace intent {
EgoStateIntent::EgoStateIntent() {}
EgoStateIntent::~EgoStateIntent() {}
void EgoStateIntent::setup() {
    egoStateTopic.velocity            = {0.0F, 0.0F};
    egoStateTopic.acceleration        = {0.0F, 0.0F};
    egoStateTopic.angularVelocity     = 0.0F;
    egoStateTopic.angularAcceleration = 0.0F;
}

void EgoStateIntent::tick() {
    if (!vehicleResponseTopic.isValid) {
        // TODO update ego state using history information
        return;
    }

    const float encoderVx =
      (vehicleResponseTopic.encoderSpeed[0U] + vehicleResponseTopic.encoderSpeed[1U] +
       vehicleResponseTopic.encoderSpeed[2U] + vehicleResponseTopic.encoderSpeed[3U]) /
      4.0F;
    const float encoderVy =
      (vehicleResponseTopic.encoderSpeed[0U] - vehicleResponseTopic.encoderSpeed[1U] +
       vehicleResponseTopic.encoderSpeed[2U] - vehicleResponseTopic.encoderSpeed[3U]) /
      4.0F;

    const data::Vector2D encoderVelocity {encoderVx, encoderVy};
    const data::Vector2D velocity = encoderVelocity * (utils::math::PI * 0.06F / 4096.0F);

    egoStateTopic.velocity = utils::math::to<data::PolarVector2D>(velocity);

    // egoStateTopic.velocity.orientation = randomDistribution_(randomGen_) * 3.9F;
    // egoStateTopic.velocity.value       = randomDistribution_(randomGen_) * 3.0 + 0.5;

    // egoStateTopic.acceleration.orientation = randomDistribution_(randomGen_) * 39.4F;
    // egoStateTopic.acceleration.value       = randomDistribution_(randomGen_) * 4.7;
}


}    // namespace intent
}    // namespace cooboc