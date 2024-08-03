#include "intents/intent_manager.h"
#include "intents/behavior_generator/behavior_generator_intent.h"
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include "intents/intent_base.h"
#include "intents/odometry_intent/odometry_intent.h"
#include "intents/route_provision_intent/route_provision_intent.h"

namespace cooboc {
namespace intent {

IntentManager::IntentManager() {
    // Localization
    intents_.push_back(new OdometryIntent());
    // The specific task that ego need to do based on the result of localization
    intents_.push_back(new BehaviorGeneratorIntent());
    // The route that ego need to follow based on the task and localization
    intents_.push_back(new RouteProvisionIntent());
    // Debug
    intents_.push_back(new DebugWriterIntent());
}
IntentManager::~IntentManager() {
    for (IntentBase *intentPtr : intents_) { delete (intentPtr); }
}
void IntentManager::setup() {
    for (IntentBase *intentPtr : intents_) { intentPtr->setup(); }
}

void IntentManager::tick() {
    for (IntentBase *intentPtr : intents_) { intentPtr->tick(); }
}


}    // namespace intent
}    // namespace cooboc