#include "intents/topics/topics.h"
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

SystemDebugTopic systemDebugTopic {};
OdometryTopic odometryTopic {};
EgoMotionStateTopic egoMotionStateTopic {};
RouteTopic routeTopic {};
BehaviorTopic behaviorTopic {};
MotionPlanningTopic motionPlanningTopic {};
MotionPlanningDebugTopic motionPlanningDebugTopic {};
ReferencePathTopic referencePathTopic {};
VehicleResponseTopic vehicleResponseTopic {};
VehicleRequestTopic vehicleRequestTopic {};


}    // namespace intent
}    // namespace cooboc