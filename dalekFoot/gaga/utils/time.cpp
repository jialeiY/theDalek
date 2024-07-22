#include "utils/time.h"
#include <cstdint>
#include "common/data_defs/timestamp.h"
#include "hal/board_def.h"

namespace cooboc {
namespace utils {
namespace time {
Timestamp now() {
    const std::uint32_t tick1  = uwTick;
    const std::uint32_t count1 = SysTick->VAL;    // count down 180000
    const std::uint32_t count2 = SysTick->VAL;

    if (count2 > count1) {
        // systick increased, timer reset
        return Timestamp(uwTick, count2);
    } else {
        return Timestamp(tick1, count2);
    }
}
}    // namespace time
}    // namespace utils
}    // namespace cooboc