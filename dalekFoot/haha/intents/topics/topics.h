#ifndef __INTENTS_TOPICS_TOPICS_H__
#define __INTENTS_TOPICS_TOPICS_H__

#include "intents/topics/behavior_topic.h"
#include "intents/topics/ego_state_topic.h"
#include "intents/topics/motion_planning_debug_topic.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/trajectory_topic.h"
#include "intents/topics/vehicle_response_topic.h"

namespace cooboc {
namespace intent {

extern OdometryTopic odometryTopic;
extern EgoStateTopic egoStateTopic;
extern RouteTopic routeTopic;
extern BehaviorTopic behaviorTopic;
extern MotionPlanningDebugTopic motionPlanningDebugTopic;
extern TrajectoryTopic trajectoryTopic;
extern VehicleResponseTopic vehicleResponseTopic;
}    // namespace intent
}    // namespace cooboc

#endif
