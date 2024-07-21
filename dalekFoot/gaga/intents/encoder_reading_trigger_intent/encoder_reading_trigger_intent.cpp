#include "intents/encoder_reading_trigger_intent/encoder_reading_trigger_intent.h"
#include "hal/hal.h"

namespace cooboc {
namespace intents {
EncoderReadingTriggerIntent::EncoderReadingTriggerIntent() {}
void EncoderReadingTriggerIntent::setup() {}
void EncoderReadingTriggerIntent::tick() {
    //
    hal::gagaI2C.read(0x36, 0x0E, 2U);
}
}    // namespace intents
}    // namespace cooboc