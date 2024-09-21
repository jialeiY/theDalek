#ifndef __GAGA_COMMON_DATA_DEFS_VEHICLE_RESPONSE_TOPIC_H__
#define __GAGA_COMMON_DATA_DEFS_VEHICLE_RESPONSE_TOPIC_H__

#include "common/data_defs/wheel_odometry.h"
#include "data/gh_protocol.h"

namespace cooboc {
namespace data {
struct VehicleResponseTopic {
    uint32_t tickCount {0U};
    WheelOdometry wheelOdometry[4U] {};

    std::uint8_t ghPacketBuffer[GH_PACKET_SIZE];
};
}    // namespace data
}    // namespace cooboc

#endif
