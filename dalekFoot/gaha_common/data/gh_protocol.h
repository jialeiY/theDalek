#ifndef __GAHA_COMM_DATA_GH_PROTOCOL_H__
#define __GAHA_COMM_DATA_GH_PROTOCOL_H__

#include <cstdint>

#define HG_PACKET_SIZE 160UL

namespace cooboc {
namespace comm {

struct GHPacket {
} __attribute__((packed));

struct HGPacket {
    static constexpr std::size_t kPlanningSize {10U};
    using WheelPlanning = float[10];
    WheelPlanning wheelsPlanning[4U];
} __attribute__((packed));
}    // namespace comm
}    // namespace cooboc

#endif
