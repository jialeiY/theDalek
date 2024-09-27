#include "intents/intent_manager.h"
#include <cstdint>
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
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

IntentManager::IntentManager() : tickCount_ {0U}, lastTickEndTime_ {0U}, lastTickDuration_ {0U} {
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
    tickCount_                        = 0U;
    lastTickEndTime_                  = 0U;
    lastTickDuration_                 = 0U;
    systemDebugTopic.lastTickEndTime  = 0U;
    systemDebugTopic.lastTickDuration = 0U;
    systemDebugTopic.tickStartTime    = 0U;
    systemDebugTopic.tickCount        = 0U;
}

void IntentManager::updateVehicleResponse(const comm::GHPacket &vehicleResponse) {
    // // TODO: setup the vehicle topic
    // vehicleResponseTopic.response = vehicleResponse;

    std::uint32_t expectedCrc = utils::math::calculateCrc(vehicleResponse);
    if (vehicleResponse.crc == expectedCrc) {
        vehicleResponseTopic.isValid = true;
        for (std::size_t i {0U}; i < 4U; ++i) {
            intent::vehicleResponseTopic.wheelOdometry[i] = vehicleResponse.wheelOdometry[i];
            intent::vehicleResponseTopic.wheelSpeed[i]    = vehicleResponse.wheelSpeed[i];
        }
    } else {
        // Invalidate vehicle response topic
        vehicleResponseTopic.isValid = false;
    }
}

void IntentManager::tick() {
    std::uint64_t tickStartTime = utils::time::nanoseconds();
    tickCount_++;

    systemDebugTopic.lastTickEndTime  = lastTickEndTime_;
    systemDebugTopic.lastTickDuration = lastTickDuration_;
    systemDebugTopic.tickStartTime    = tickStartTime;
    systemDebugTopic.tickCount        = tickCount_;

    std::printf("\r\n=======\r\n");
    for (IntentBase *intentPtr : intents_) { intentPtr->tick(); }

    lastTickEndTime_  = utils::time::nanoseconds();
    lastTickDuration_ = lastTickEndTime_ - tickStartTime;
}


comm::HGPacket IntentManager::getGhPacket() const {
    comm::HGPacket packet = *reinterpret_cast<comm::HGPacket *>(vehicleRequestTopic.hgPacketBuffer);
    return packet;
}

}    // namespace intent
}    // namespace cooboc