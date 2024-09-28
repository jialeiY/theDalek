#ifndef __DATA_CODEC_EGO_MOTION_STATE_TOPIC_CODEC_H__
#define __DATA_CODEC_EGO_MOTION_STATE_TOPIC_CODEC_H__

#include "gen/data/proto/ego_motion_state_topic.pb.h"
#include "intents/topics/ego_motion_state_topic.h"

namespace cooboc {
namespace data {
proto::EgoMotionStateTopic convert(const intent::EgoMotionStateTopic &);
}    // namespace data


}    // namespace cooboc


#endif
