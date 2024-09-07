#include "data/codec/system_debug_codec.h"
#include "gen/data/proto/system_debug_topic.pb.h"
#include "intents/topics/system_debug_topic.h"

namespace cooboc {
namespace data {
proto::SystemDebugTopic convert(const intent::SystemDebugTopic &in) {
    proto::SystemDebugTopic out;
    out.set_lasttickendtime(in.lastTickEndTime);
    out.set_lasttickduration(in.lastTickDuration);
    out.set_tickstarttime(in.tickStartTime);
    out.set_tickcount(in.tickCount);
    return out;
}
}    // namespace data
}    // namespace cooboc
