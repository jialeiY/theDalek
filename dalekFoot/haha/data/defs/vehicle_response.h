#ifndef __DATA_DEFS_VEHICLE_RESPONSE_H__
#define __DATA_DEFS_VEHICLE_RESPONSE_H__

#include <cstdint>

namespace cooboc {
namespace data {

struct WheelStatus {
    uint64_t encoder {0U};
    float speed {0.0F};
};

struct VehicleResponse {
    WheelStatus wheelStatus[4];
};
}    // namespace data
}    // namespace cooboc
#endif
