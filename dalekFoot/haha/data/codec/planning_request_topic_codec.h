#ifndef __DATA_CODEC_PLANNING_REQUEST_TOPIC_CODEC_H__
#define __DATA_CODEC_PLANNING_REQUEST_TOPIC_CODEC_H__

#include <gen/data/proto/planning_request_topic.pb.h>
#include <intents/topics/planning_request_topic.h>


namespace cooboc {
namespace data {

proto::PlanningRequestTopic convert(const intent::PlanningRequestTopic &in);


}    // namespace data
}    // namespace cooboc


#endif