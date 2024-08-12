#ifndef __DATA_CODEC_BEHAVIOR_TOPIC_CODEC_H__
#define __DATA_CODEC_BEHAVIOR_TOPIC_CODEC_H__

#include "gen/data/proto/behavior_topic.pb.h"
#include "intents/topics/behavior_topic.h"


namespace cooboc {
namespace data {

proto::BehaviorTopic convert(const intent::BehaviorTopic &in);


}    // namespace data
}    // namespace cooboc


#endif