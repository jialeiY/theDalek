#include "intents/debug_data_intent/debug_data_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"


namespace cooboc {
namespace intents {
void DebugDataIntent::setup() {}
void DebugDataIntent::tick() {
    hal::gagaSerial.println("%d,%d,%d,%d\r\n",
                            (int)(data::encoderReadingOutput.encoder[0].value),
                            (int)(data::encoderReadingOutput.encoder[1].value),
                            (int)(data::encoderReadingOutput.encoder[2].value),
                            (int)(data::encoderReadingOutput.encoder[3].value));
}
}    // namespace intents
}    // namespace cooboc