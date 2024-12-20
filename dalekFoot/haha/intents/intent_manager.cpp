#include "intents/intent_manager.h"
#include <cstdint>
#include <cstdio>
#include "intents/behavior_intent/behavior_intent.h"
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include "intents/ego_motion_state_intent/ego_motion_state_intent.h"
#include "intents/intent_base.h"
#include "intents/motion_planning_intent/motion_planning_intent.h"
#include "intents/odometry_intent/odometry_intent.h"
#include "intents/reference_path_intent/reference_path_intent.h"
#include "intents/route_intent/route_intent.h"
#include "intents/topics/topics.h"
#include "intents/topics/vehicle_request_topic.h"
#include "intents/vehicle_request_intent/vehicle_request_intent.h"
#include "utils/math.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

IntentManager::IntentManager() : tickCount_ {0U}, lastTickEndTime_ {0U}, lastTickDuration_ {0U} {
    // Decode vehicle status from gaga response, generate ego_motion
    intents_.push_back(new EgoMotionStateIntent());
    // Localization
    intents_.push_back(new OdometryIntent());
    // The specific task that ego need to do based on the result of localization
    intents_.push_back(new BehaviorIntent());
    // The route that ego need to follow based on the task and localization
    intents_.push_back(new RouteIntent());
    // ReferencePathIntent read the Routes from RouteIntent and out put the trajectory that vehicle
    // can follow
    intents_.push_back(new ReferencePathIntent());
    // MotionPlanning plan the waypoints of maneuver state of ego based on all
    intents_.push_back(new MotionPlanningIntent());
    // VehicleRequestIntent generate communication packet to GAGA
    intents_.push_back(new VehicleRequestIntent());
    // information Debug
    intents_.push_back(new DebugWriterIntent());
}
IntentManager::~IntentManager() {
    for (IntentBase *intentPtr : intents_) {
        delete (intentPtr);
    }
}
void IntentManager::setup() {
    for (IntentBase *intentPtr : intents_) {
        intentPtr->setup();
    }
    tickCount_                                = 0U;
    lastTickEndTime_                          = 0U;
    lastTickDuration_                         = 0U;
    shared::systemDebugTopic.lastTickEndTime  = 0U;
    shared::systemDebugTopic.lastTickDuration = 0U;
    shared::systemDebugTopic.tickStartTime    = 0U;
    shared::systemDebugTopic.tickCount        = 0U;
}

void IntentManager::updateVehicleResponse(const comm::GHPacket &vehicleResponse) {
    // // TODO: setup the vehicle topic
    // vehicleResponseTopic.response = vehicleResponse;

    std::uint32_t expectedCrc = utils::math::calculateCrc(vehicleResponse);
    if (vehicleResponse.crc == expectedCrc) {
        shared::vehicleResponseTopic.isValid = true;
        for (std::size_t i {0U}; i < 4U; ++i) {
            intent::shared::vehicleResponseTopic.encoderOdometry[i] =
              vehicleResponse.encoderOdometry[i];
        }
    } else {
        // Invalidate vehicle response topic
        shared::vehicleResponseTopic.isValid   = false;
        shared::vehicleResponseTopic.tickCount = vehicleResponse.tickCount;
    }
}

void IntentManager::tick() {
    std::uint64_t tickStartTime = utils::time::nanoseconds();
    tickCount_++;

    shared::systemDebugTopic.lastTickEndTime  = lastTickEndTime_;
    shared::systemDebugTopic.lastTickDuration = lastTickDuration_;
    shared::systemDebugTopic.tickStartTime    = tickStartTime;
    shared::systemDebugTopic.tickCount        = tickCount_;

    std::printf("\r\n=======\r\n");
    for (IntentBase *intentPtr : intents_) {
        intentPtr->tick();
    }

    lastTickEndTime_  = utils::time::nanoseconds();
    lastTickDuration_ = lastTickEndTime_ - tickStartTime;
}


comm::HGPacket IntentManager::getGhPacket() const {
    comm::HGPacket packet =
      *reinterpret_cast<comm::HGPacket *>(shared::vehicleRequestTopic.hgPacketBuffer);
    return packet;
}

}    // namespace intent
}    // namespace cooboc