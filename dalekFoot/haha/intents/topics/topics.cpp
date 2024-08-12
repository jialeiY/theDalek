#include "intents/topics/topics.h"
#include "intents/topics/behavior_topic.h"
#include "intents/topics/ego_state_topic.h"
#include "intents/topics/motion_planning_debug_topic.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/trajectory_topic.h"

namespace cooboc {
namespace intent {

OdometryTopic odometryTopic {};
EgoStateTopic egoStateTopic {};
RouteTopic routeTopic {};
BehaviorTopic behaviorTopic {};
MotionPlanningDebugTopic motionPlanningDebugTopic {};
TrajectoryTopic trajectoryTopic {};

}    // namespace intent
}    // namespace cooboc