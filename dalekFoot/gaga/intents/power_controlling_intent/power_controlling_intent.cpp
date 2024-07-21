#include "intents/power_controlling_intent/power_controlling_intent.h"
#include "hal/hal.h"
#include "intents/common/parameters.h"


namespace cooboc {
namespace intents {
void PowerControllingIntent::setup() {}
void PowerControllingIntent::tick() {
    for (int i = 0; i < 4; ++i) {
        hal::gagaMotors[i].setPower(parameters.motorDirection[i] ? 400 : -400);
    }
}
}    // namespace intents
}    // namespace cooboc