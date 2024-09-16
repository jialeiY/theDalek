#include "intents/target_maneuver_intent/target_maneuver_intent.h"
#include <cmath>
#include "hal/hal.h"
#include "intents/common/data_pool.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intents {

void TargetManeuverIntent::setup() {
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::targetManeuverTopic.speed[i] = 0.0F;
    }
}
void TargetManeuverIntent::tick() {
    // {
    //     // square wave
    //     std::uint32_t time = utils::time::now().milliseconds();
    //     time %= 1000;
    //     float target = 0.0F;
    //     if (time < 500) {
    //         target = 0.1F;
    //     } else {
    //         target = 0.3F;
    //     }


    //     for (std::size_t i {0U}; i < 4U; ++i) {
    //         data::targetManeuverTopic.speed[i] = target;
    //     }
    // }

    // {
    //     // cycle = 500 milli seconds
    //     // amplifer = 0.1 -> 0.4
    //     std::uint32_t time = utils::time::now().milliseconds();
    //     constexpr int cycle {500};
    //     // const float timeShift = static_cast<float>(time % cycle) * 2.0F *
    //     // utils::math::PI / static_cast<float>(cycle);
    //     for (std::size_t i {0U}; i < 4U; ++i) {
    //         const float timeShift =
    //           static_cast<float>((time + i * cycle / 4) % cycle) * 2.0F *
    //           utils::math::PI / static_cast<float>(cycle);
    //         data::targetManeuverTopic.speed[i] =
    //           utils::math::lerp(std::sin(timeShift), -1.0F, 1.0F, 0.03F,
    //           0.1F);
    //     }
    // }

    // {
    //     // square wave


    //     for (std::size_t i {0U}; i < 4U; ++i) {
    //         std::uint32_t time = utils::time::now().milliseconds();
    //         time += i * 250;
    //         time %= 1000;
    //         float target = 0.0F;
    //         if (time < 500) {
    //             target = 0.1F;
    //         } else {
    //             target = 0.3F;
    //         }
    //         data::targetManeuverTopic.speed[i] = target;
    //     }
    //     data::targetManeuverTopic.speed[1U] = 0.2;
    //     data::targetManeuverTopic.speed[2U] = 0.3;
    // }
}

}    // namespace intents
}    // namespace cooboc