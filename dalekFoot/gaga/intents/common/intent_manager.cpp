#include "intents/common/intent_manager.h"
#include <tuple>
#include "intent_base.h"
#include "intents/power_controlling_intent/power_controlling_intent.h"

namespace cooboc {
namespace intents {

IntentManager::IntentManager() {}
void IntentManager::setup() {
    // Initialize PubSubStub
    // pubSubStub_.registerTopic<data::MotorsPowerRequestTopic>();

    // Instance all intents
    IntentBase *powerControllingIntent = new PowerControllingIntent();
    powerControllingIntent->setup();
    std::ignore = powerControllingIntent;
}
void IntentManager::launch() {}
void IntentManager::tick() {}


IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc
