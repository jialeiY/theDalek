#include "intents/target_maneuver_intent/target_maneuver_intent.h"
#include "intents/common/data_pool.h"

namespace cooboc {
namespace intents {

void TargetManeuverIntent::setup() {
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::targetManeuverTopic.speed[i] = 2.0F;
    }
}
void TargetManeuverIntent::tick() {}

}    // namespace intents
}    // namespace cooboc