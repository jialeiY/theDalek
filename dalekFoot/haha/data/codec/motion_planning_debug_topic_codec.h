#ifndef __DATA_CODEC_MOTION_PLANNING_DEBUG_TOPIC_CODEC_H__
#define __DATA_CODEC_MOTION_PLANNING_DEBUG_TOPIC_CODEC_H__

#include "gen/data/proto/motion_planning_debug_topic.pb.h"
#include "intents/topics/motion_planning_debug_topic.h"

namespace cooboc {
namespace data {

proto::MotionPlanningDebugTopic convert(const intent::MotionPlanningDebugTopic &in);


}    // namespace data
}    // namespace cooboc


#endif