#ifndef __INTENTS_COMMON_DATA_DEFS_QUALIFIER_H__
#define __INTENTS_COMMON_DATA_DEFS_QUALIFIER_H__

#include <cstdint>

namespace cooboc {
namespace data {
enum class Qualifier : std::uint8_t {
    BAD      = 0U,
    DEGRADED = 1U,
    GOOD     = 2U,

};
}    // namespace data
}    // namespace cooboc

#endif
