#ifndef __COMMON_DATA_DEFS_TIMESTAMP_H__
#define __COMMON_DATA_DEFS_TIMESTAMP_H__

#include <cstdint>

struct Timestamp {
    Timestamp(const std::uint32_t systick, const std::uint32_t systickVal) :
        systick_ {systick},
        systickVal_ {systickVal} {}

  private:
    const std::uint32_t systick_;
    const std::uint32_t systickVal_;
};

#endif
