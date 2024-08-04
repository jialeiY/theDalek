#ifndef __INTENTS_TOPICS_TOPICS_H__
#define __INTENTS_TOPICS_TOPICS_H__

#include "intents/topics/ego_state_topic.h"
#include "intents/topics/motion_planning_debug_topic.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/planning_request_topic.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {

extern OdometryTopic odometryTopic;
extern EgoStateTopic egoStateTopic;
extern RouteTopic routeTopic;
extern PlanningRequestTopic planningRequestTopic;
extern MotionPlanningDebugTopic motionPlanningDebugTopic;

}    // namespace intent
}    // namespace cooboc

#endif
