#include "intents/intent_manager.h"
#include <cstdio>
#include "data/defs/vehicle_response.h"
#include "intents/behavior_intent/behavior_intent.h"
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include "intents/ego_state_intent/ego_state_intent.h"
#include "intents/intent_base.h"
#include "intents/motion_planning_intent/motion_planning_intent.h"
#include "intents/odometry_intent/odometry_intent.h"
#include "intents/route_intent/route_intent.h"
#include "intents/topics/topics.h"
#include "intents/topics/vehicle_request_topic.h"
#include "intents/trajectory_intent/trajectory_intent.h"
#include "intents/vehicle_request_intent/vehicle_request_intent.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

IntentManager::IntentManager() {
    // Decode vehicle status from gaga response, generate ego_motion
    intents_.push_back(new EgoStateIntent());
    // Localization
    intents_.push_back(new OdometryIntent());
    // The specific task that ego need to do based on the result of localization
    intents_.push_back(new BehaviorIntent());
    // The route that ego need to follow based on the task and localization
    intents_.push_back(new RouteIntent());
    // TrajectoryIntent read the Routes from RouteIntent and out put the trajectory that vehicle can
    // follow
    intents_.push_back(new TrajectoryIntent());
    // MotionPlanning plan the waypoints of maneuver state of ego based on all
    intents_.push_back(new MotionPlanningIntent());
    // VehicleRequestIntent generate communication packet to GAGA
    intents_.push_back(new VehicleRequestIntent());
    // information Debug
    intents_.push_back(new DebugWriterIntent());
}
IntentManager::~IntentManager() {
    for (IntentBase *intentPtr : intents_) { delete (intentPtr); }
}
void IntentManager::setup() {
    for (IntentBase *intentPtr : intents_) { intentPtr->setup(); }
}

void IntentManager::updateVehicleResponse(data::VehicleResponse vehicleResponse) {
    // TODO: setup the vehicle topic
    vehicleResponseTopic.response = vehicleResponse;
}

void IntentManager::tick() {
    systemDebugTopic.cycleStartTime = utils::time::nanoseconds();
    systemDebugTopic.cycleEndTime   = 0U;

    std::printf("\r\n=======\r\n");
    for (IntentBase *intentPtr : intents_) { intentPtr->tick(); }
}


}    // namespace intent
}    // namespace cooboc