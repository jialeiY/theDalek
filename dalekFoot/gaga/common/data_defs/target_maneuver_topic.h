#ifndef __COMMON_DATA_DEFS_TARGET_MANEUVER_TOPIC_H__
#define __COMMON_DATA_DEFS_TARGET_MANEUVER_TOPIC_H__

#include <cstdint>

namespace cooboc {
namespace data {

enum class ManeuverRequestSource : std::uint8_t {
    NEW_VEHICLE_REQUEST,
    OLD_VEHICLE_REQUEST,
    FAILSAFE
};


struct TargetManeuverTopic {
    ManeuverRequestSource source {ManeuverRequestSource::FAILSAFE};
    std::uint64_t requestId {0U};
    std::uint32_t tickCount {0U};
    float speed[4U] {0.0F};    // m/s
};
}    // namespace data
}    // namespace cooboc

#endif
