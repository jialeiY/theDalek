#ifndef __GAHA_COMM_DATA_GH_PROTOCOL_H__
#define __GAHA_COMM_DATA_GH_PROTOCOL_H__

#include <cstdint>

#define HG_PROTOCOL_SIZE 164UL
#define HG_PACKET_SIZE   164UL
#define GH_PACKET_SIZE   24UL

namespace cooboc {
namespace comm {

struct GHPacket {
    std::int32_t wheelOdometry[4U] {};
    float wheelSpeed[4U]{};
    std::uint32_t tickCount {0U};
    std::uint32_t crc {0};
} __attribute__((packed));

struct HGPacket {
    static constexpr std::size_t kPlanningSize {10U};

    using WheelPlanning = float[10];
    WheelPlanning wheelsPlanning[4U];

    std::uint32_t crc {0};
} __attribute__((packed));


}    // namespace comm
}    // namespace cooboc

#endif
