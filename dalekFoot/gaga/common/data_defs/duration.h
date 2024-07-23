#ifndef __COMMON_DATA_DEFS_DURATION_H__
#define __COMMON_DATA_DEFS_DURATION_H__

#include <cstdint>

namespace cooboc {
namespace data {

class ns {};

struct Duration {
    bool isNagative {false};
    std::uint32_t tickDiff {0U};
    std::uint32_t counerDiff {0U};

    std::int32_t value() const {
        std::int32_t ret = tickDiff * 1000 + counerDiff / 180;
        return isNagative ? -ret : ret;
    };
};
}    // namespace data
}    // namespace cooboc

#endif
