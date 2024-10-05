#ifndef __DATA_DEFS_BEHAVIOR_ID_H__
#define __DATA_DEFS_BEHAVIOR_ID_H__

#include <cstdint>

namespace cooboc {
namespace data {


using BehaviorId = std::uint32_t;
constexpr BehaviorId kInvalidBehaviorId {0U};

inline bool isInvalid(const BehaviorId &id) {
    return id == kInvalidBehaviorId;
}

inline bool isValid(const BehaviorId &id) {
    return id != kInvalidBehaviorId;
}

}    // namespace data
}    // namespace cooboc


#endif
