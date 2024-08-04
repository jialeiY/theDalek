#include "intents/topics/topics.h"
#include "intents/topics/ego_state_topic.h"
#include "intents/topics/motion_planning_debug_topic.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/planning_request_topic.h"
#include "intents/topics/route_topic.h"

namespace cooboc {
namespace intent {

OdometryTopic odometryTopic {};
EgoStateTopic egoStateTopic {};
RouteTopic routeTopic {};
PlanningRequestTopic planningRequestTopic {};
MotionPlanningDebugTopic motionPlanningDebugTopic {};


}    // namespace intent
}    // namespace cooboc