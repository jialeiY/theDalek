#ifndef __DATA_CODEC_MOTION_PLANNING_TOPIC_TOPIC_CODEC_H__
#define __DATA_CODEC_MOTION_PLANNING_TOPIC_TOPIC_CODEC_H__

#include "gen/data/proto/motion_planning_topic.pb.h"
#include "intents/topics/motion_planning_topic.h"

namespace cooboc {
namespace data {

proto::MotionPlanningTopic convert(const intent::MotionPlanningTopic &in);


}    // namespace data
}    // namespace cooboc


#endif