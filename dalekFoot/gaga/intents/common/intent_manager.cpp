#include "intents/common/intent_manager.h"
#include <tuple>
#include "hal/board_def.h"
#include "intent_base.h"
#include "intents/common/parameters.h"
#include "intents/debug_data_intent/debug_data_intent.h"
#include "intents/encoder_reading_intent/encoder_reading_intent.h"
#include "intents/encoder_reading_trigger_intent/encoder_reading_trigger_intent.h"
#include "intents/power_controlling_intent/power_controlling_intent.h"
#include "intents/target_maneuver_intent/target_maneuver_intent.h"
#include "intents/wheel_odometry_intent/wheel_odometry_intent.h"

namespace cooboc {
namespace intents {

IntentManager::IntentManager() {}
void IntentManager::setup() {
    setupParameters();

    // Instance all intents
    intents_[0U] = new EncoderReadingTriggerIntent();
    intents_[1U] = new TargetManeuverIntent();
    intents_[2U] = new WheelOdometryIntent();
    intents_[3U] = new PowerControllingIntent();
    intents_[4U] = new EncoderReadingIntent();
    intents_[5U] = new DebugDataIntent();

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
