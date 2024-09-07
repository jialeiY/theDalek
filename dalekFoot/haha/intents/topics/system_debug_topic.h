#ifndef __INTENTS_TOPIC_SYSTEM_DEBUG_TOPIC_H__
#define __INTENTS_TOPIC_SYSTEM_DEBUG_TOPIC_H__

#include <cstdint>

namespace cooboc {
namespace intent {
struct SystemDebugTopic {
    std::uint64_t lastTickEndTime {0U};
    std::uint64_t lastTickDuration {0U};

    std::uint64_t tickStartTime {0U};
    std::uint64_t tickCount {0U};
};
}    // namespace intent
}    // namespace cooboc

#endif
