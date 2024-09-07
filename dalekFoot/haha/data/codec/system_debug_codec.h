#ifndef __DATA_CODEC_SYSTEM_DEBUG_CODEC_H__
#define __DATA_CODEC_SYSTEM_DEBUG_CODEC_H__

#include "gen/data/proto/system_debug_topic.pb.h"
#include "intents/topics/system_debug_topic.h"

namespace cooboc {
namespace data {
proto::SystemDebugTopic convert(const intent::SystemDebugTopic &in);
}
}    // namespace cooboc

#endif
