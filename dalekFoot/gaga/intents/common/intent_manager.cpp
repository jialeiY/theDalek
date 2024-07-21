#include "intents/common/intent_manager.h"
#include <tuple>
#include "hal/board_def.h"
#include "intent_base.h"
#include "intents/debug_data_intent/debug_data_intent.h"
#include "intents/encoder_reading_intent/encoder_reading_intent.h"
#include "intents/encoder_reading_trigger_intent/encoder_reading_trigger_intent.h"
#include "intents/power_controlling_intent/power_controlling_intent.h"
#include "intents/wheel_odometry_intent/wheel_odometry_intent.h"

namespace cooboc {
namespace intents {

IntentManager::IntentManager() {}
void IntentManager::setup() {
    // Initialize PubSubStub
    // pubSubStub_.registerTopic<data::MotorsPowerRequestTopic>();

    // Instance all intents
    intents_[0U] = new EncoderReadingTriggerIntent();
    intents_[1U] = new WheelOdometryIntent();
    intents_[2U] = new PowerControllingIntent();
    intents_[3U] = new EncoderReadingIntent();
    intents_[4U] = new DebugDataIntent();

    for (IntentBase *intentP : intents_) { intentP->setup(); }
}

void IntentManager::tick() {
    // Set the LED OFF
    LED1_OFF;

    for (IntentBase *intentP : intents_) { intentP->tick(); }

    // Set the LED ON
    LED1_ON;
}


IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc
