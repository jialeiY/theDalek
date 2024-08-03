#ifndef __DATA_CODEC_ROUTE_TOPIC_CODEC_H__
#define __DATA_CODEC_ROUTE_TOPIC_CODEC_H__

#include "gen/data/proto/route_topic.pb.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace data {
proto::RouteTopic convert(const intent::RouteTopic &);
}    // namespace data
}    // namespace cooboc

#endif
