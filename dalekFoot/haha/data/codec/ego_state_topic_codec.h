#ifndef __DATA_CODEC_EGO_STATE_TOPIC_CODEC_H__
#define __DATA_CODEC_EGO_STATE_TOPIC_CODEC_H__

#include "gen/data/proto/ego_state_topic.pb.h"
#include "intents/topics/ego_state_topic.h"

namespace cooboc {
namespace data {
proto::EgoStateTopic convert(const intent::EgoStateTopic &);
}    // namespace data


}    // namespace cooboc


#endif
