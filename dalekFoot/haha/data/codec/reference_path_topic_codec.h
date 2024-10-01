#ifndef __DATA_CODEC_REFERENCE_PATH_TOPIC_CODEC_H__
#define __DATA_CODEC_REFERENCE_PATH_TOPIC_CODEC_H__

#include "gen/data/proto/reference_path_topic.pb.h"
#include "intents/topics/reference_path_topic.h"

namespace cooboc {
namespace data {
proto::ReferencePathTopic convert(const intent::ReferencePathTopic &);
}    // namespace data
}    // namespace cooboc

#endif
