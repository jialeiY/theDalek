#ifndef __GAHA_COMM_DATA_GH_PROTOCOL_H__
#define __GAHA_COMM_DATA_GH_PROTOCOL_H__

#include <cstdint>

#define HG_PROTOCOL_SIZE 164UL
#define HG_PACKET_SIZE   164UL
#define GH_PACKET_SIZE   40UL

namespace cooboc {
namespace comm {

// Haha -> Gaga  Control Request

struct  HGPacket {
    static constexpr std::size_t kPlanningSize {10U};
    float wheelEncoderPlanning[4U][kPlanningSize];
    std::uint32_t crc {0};
};



// Gaga -> Haha Sensor Response

struct __attribute__((packed)) GHPacket {
    std::uint32_t tickCount {0U};
    std::int32_t encoderOdometry[4U] {}; // the absolute odometry of encoder, so that if one packet is missing, whole odometry could be deduced.
    std::int32_t intervalOdometry[4U] {}; // the odometry of encoder between two communication

    std::uint32_t crc {0};
} ;




}    // namespace comm
}    // namespace cooboc

#endif
