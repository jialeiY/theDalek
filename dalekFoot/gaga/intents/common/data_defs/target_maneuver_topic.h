#ifndef __INTENTS_COMMON_DATA_DEFS_TARGET_MANEUVER_TOPIC_H__
#define __INTENTS_COMMON_DATA_DEFS_TARGET_MANEUVER_TOPIC_H__

namespace cooboc {
namespace data {
struct TargetManeuverTopic {
    float speed[4U] {0.0F};    // m/s
};
}    // namespace data
}    // namespace cooboc

#endif
