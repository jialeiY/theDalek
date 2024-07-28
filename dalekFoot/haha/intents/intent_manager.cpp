#include "intents/intent_manager.h"
#include <intents/behavior_generator/behavior_generator_intent.h>
#include <intents/debug_writer_intent/debug_writer_intent.h>
#include <intents/intent_base.h>


namespace cooboc {
namespace intent {

IntentManager::IntentManager() {
    intents_[0] = new BehaviorGeneratorIntent();
    intents_[1] = new DebugWriterIntent();
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