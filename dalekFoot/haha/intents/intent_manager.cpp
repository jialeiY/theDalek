#include "intents/intent_manager.h"
#include "intents/behavior_generator/behavior_generator_intent.h"
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include "intents/intent_base.h"
#include "intents/odometry_intent/odometry_intent.h"

namespace cooboc {
namespace intent {

IntentManager::IntentManager() {
    intents_.push_back(new OdometryIntent());
    intents_.push_back(new BehaviorGeneratorIntent());
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