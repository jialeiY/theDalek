#ifndef __INTENTS_TOPICS_TOPICS_H__
#define __INTENTS_TOPICS_TOPICS_H__

#include "intents/topics/odometry_topic.h"
#include "intents/topics/planning_request_topic.h"


namespace cooboc {
namespace intent {

extern OdometryTopic odometryTopic;
extern RouteTopic routeTopic;
extern PlanningRequestTopic planningRequestTopic;

}    // namespace intent
}    // namespace cooboc

#endif
