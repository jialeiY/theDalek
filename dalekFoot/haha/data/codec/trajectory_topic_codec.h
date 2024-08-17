#ifndef __DATA_CODEC_TRAJECTORY_TOPIC_CODEC_H__
#define __DATA_CODEC_TRAJECTORY_TOPIC_CODEC_H__

#include "gen/data/proto/trajectory_topic.pb.h"
#include "intents/topics/trajectory_topic.h"

namespace cooboc {
namespace data {
proto::TrajectoryTopic convert(const intent::TrajectoryTopic &);
}    // namespace data
}    // namespace cooboc

#endif
