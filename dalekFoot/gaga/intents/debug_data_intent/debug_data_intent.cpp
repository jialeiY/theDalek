#include "intents/debug_data_intent/debug_data_intent.h"
#include "hal/hal.h"

namespace cooboc {
namespace intents {
void DebugDataIntent::setup() {}
void DebugDataIntent::tick() { hal::gagaSerial.println("0\r\n"); }
}    // namespace intents
}    // namespace cooboc