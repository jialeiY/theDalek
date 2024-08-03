#ifndef __DATA_CODEC_ODOMETRY_TOPIC_CODEC_H__
#define __DATA_CODEC_ODOMETRY_TOPIC_CODEC_H__

#include "gen/data/proto/odometry_topic.pb.h"
#include "intents/topics/odometry_topic.h"

namespace cooboc {
namespace data {
proto::OdometryTopic convert(const intent::OdometryTopic &);
}
}    // namespace cooboc

#endif
