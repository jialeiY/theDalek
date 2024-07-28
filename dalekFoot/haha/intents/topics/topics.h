#ifndef __INTENTS_TOPICS_TOPICS_H__
#define __INTENTS_TOPICS_TOPICS_H__

#include <data/defs/odometry.h>
#include <intents/topics/planning_request_topic.h>


namespace cooboc {
namespace intent {

struct OdometryTopic {
    data::Odometry odometry;
};


extern PlanningRequestTopic planningRequestTopic;

}    // namespace intent
}    // namespace cooboc

#endif
