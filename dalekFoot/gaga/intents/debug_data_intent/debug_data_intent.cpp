#include "intents/debug_data_intent/debug_data_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"


namespace cooboc {
namespace intents {
void DebugDataIntent::setup() {}
void DebugDataIntent::tick() {
    const auto value {data::encoderReadingOutput.encoder[0].value};

    hal::gagaSerial.println("%d\r\n", (int)(value));
}
}    // namespace intents
}    // namespace cooboc