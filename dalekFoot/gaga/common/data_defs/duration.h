#ifndef __COMMON_DATA_DEFS_DURATION_H__
#define __COMMON_DATA_DEFS_DURATION_H__

#include <cstdint>

namespace cooboc {
namespace data {

struct Duration {
    bool isNagative {false};
    std::uint32_t tickDiff {0U};
    std::uint32_t counerDiff {0U};

    std::int32_t nanoseconds() const {
        std::int32_t ret = tickDiff * 1000 + counerDiff / 180;
        return isNagative ? -ret : ret;
    }
    std::int32_t milliseconds() const {
        const std::int32_t ret = tickDiff;
        return isNagative ? -ret : ret;
    }
    float seconds() const {
        float ret = static_cast<float>(tickDiff) / 1000.0F;
        ret += static_cast<float>(counerDiff) / 180000000.0F;
        return isNagative ? -ret : ret;
    }
};
}    // namespace data
}    // namespace cooboc

#endif
