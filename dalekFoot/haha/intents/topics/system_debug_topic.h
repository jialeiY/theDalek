#ifndef __INTENTS_TOPIC_SYSTEM_DEBUG_TOPIC_H__
#define __INTENTS_TOPIC_SYSTEM_DEBUG_TOPIC_H__

#include <cstdint>

namespace cooboc {
namespace intent {
struct SystemDebugTopic {
    std::uint64_t cycleStartTime {0U};
    std::uint64_t cycleEndTime {0U};
};
}    // namespace intent
}    // namespace cooboc

#endif
