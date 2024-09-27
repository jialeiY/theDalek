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
    float vx = (vehicleResponseTopic.wheelSpeed[0U] + vehicleResponseTopic.wheelSpeed[1U] +
                vehicleResponseTopic.wheelSpeed[2U] + vehicleResponseTopic.wheelSpeed[3U]) /
               4.0F;
    float vy = (vehicleResponseTopic.wheelSpeed[0U] - vehicleResponseTopic.wheelSpeed[1U] +
                vehicleResponseTopic.wheelSpeed[2U] - vehicleResponseTopic.wheelSpeed[3U]) /
               4.0F;

    data::Vector2D velocity {vx, vy};

    egoStateTopic.velocity = utils::math::to<data::PolarVector2D>(velocity);

    // egoStateTopic.velocity.orientation = randomDistribution_(randomGen_) * 3.9F;
    // egoStateTopic.velocity.value       = randomDistribution_(randomGen_) * 3.0 + 0.5;

    // egoStateTopic.acceleration.orientation = randomDistribution_(randomGen_) * 39.4F;
    // egoStateTopic.acceleration.value       = randomDistribution_(randomGen_) * 4.7;
}


}    // namespace intent
}    // namespace cooboc