#include "intents/ego_state_intent/ego_state_intent.h"
#include "intents/topics/topics.h"


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
    egoStateTopic.velocity = {0.0F, vehicleResponseTopic.response.wheelStatus[0].speed};

    // egoStateTopic.velocity.orientation = randomDistribution_(randomGen_) * 3.9F;
    // egoStateTopic.velocity.value       = randomDistribution_(randomGen_) * 3.0 + 0.5;

    // egoStateTopic.acceleration.orientation = randomDistribution_(randomGen_) * 39.4F;
    // egoStateTopic.acceleration.value       = randomDistribution_(randomGen_) * 4.7;
}


}    // namespace intent
}    // namespace cooboc