#ifndef __GAGA_COMMON_DATA_DEFS_VEHICLE_REQUEST_TOPIC_H__
#define __GAGA_COMMON_DATA_DEFS_VEHICLE_REQUEST_TOPIC_H__

#include <cstdint>

namespace cooboc {
namespace data {
struct VehicleRequestTopic {
    std::uint64_t requestId {0U};
    float wheel[4][10];
};
}    // namespace data
}    // namespace cooboc


#endif
