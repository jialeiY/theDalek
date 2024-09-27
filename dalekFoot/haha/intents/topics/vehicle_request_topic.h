#ifndef __INTENTS_TOPICS_VEHICLE_REQUEST_TOPIC_H__
#define __INTENTS_TOPICS_VEHICLE_REQUEST_TOPIC_H__

#include <cstdint>
#include "data/defs/polar_vector2d.h"
#include "data/defs/vector2d.h"
#include "data/gh_protocol.h"

namespace cooboc {
namespace intent {

constexpr std::size_t kControlSize {10U};

struct WheelControlPlanning {
    float encoderSpeed[kControlSize];
};

struct VehicleRequestTopic {
    WheelControlPlanning wheelControlPlanning[4];
    std::uint8_t hgPacketBuffer[HG_PACKET_SIZE];
};
}    // namespace intent
}    // namespace cooboc

#endif
