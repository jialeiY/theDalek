#include "intents/target_maneuver_intent/target_maneuver_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"
#include "utils/time.h"

namespace cooboc {
namespace intents {

void TargetManeuverIntent::setup() {
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::targetManeuverTopic.speed[i] = 0.0F;
    }
}
void TargetManeuverIntent::tick() {
    data::Timepoint now = utils::time::now();
    data::Timepoint zero;
    data::Duration d = now - zero;
    int time         = static_cast<int>(d.milliseconds());
    time %= 1000;
    float target = 0.0F;
    if (time < 500) {
        target = 0.1F;
    } else {
        target = 0.3F;
    }

    for (std::size_t i {0U}; i < 4U; ++i) {
        data::targetManeuverTopic.speed[i] = target;
    }
}

}    // namespace intents
}    // namespace cooboc