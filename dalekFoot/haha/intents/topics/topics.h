#ifndef __INTENTS_TOPICS_TOPICS_H__
#define __INTENTS_TOPICS_TOPICS_H__

#include "intents/topics/behavior_topic.h"
#include "intents/topics/ego_motion_state_topic.h"
#include "intents/topics/motion_planning_debug_topic.h"
#include "intents/topics/motion_planning_topic.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/reference_path_topic.h"
#include "intents/topics/route_topic.h"
#include "intents/topics/system_debug_topic.h"
#include "intents/topics/vehicle_request_topic.h"
#include "intents/topics/vehicle_response_topic.h"

namespace cooboc {
namespace intent {

extern SystemDebugTopic systemDebugTopic;
extern OdometryTopic odometryTopic;
extern EgoMotionStateTopic egoMotionStateTopic;
extern RouteTopic routeTopic;
extern BehaviorTopic behaviorTopic;
extern MotionPlanningTopic motionPlanningTopic;
extern MotionPlanningDebugTopic motionPlanningDebugTopic;
extern ReferencePathTopic referencePathTopic;
extern VehicleResponseTopic vehicleResponseTopic;
extern VehicleRequestTopic vehicleRequestTopic;


}    // namespace intent
}    // namespace cooboc

#endif
