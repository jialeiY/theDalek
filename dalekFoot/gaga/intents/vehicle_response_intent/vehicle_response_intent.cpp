#include "intents/vehicle_response_intent/vehicle_response_intent.h"
#include <cstdint>
#include "data/gh_protocol.h"
#include "intents/common/data_pool.h"

namespace cooboc {
namespace intents {
void VehicleResponseIntent::setup() { reset(); }

void VehicleResponseIntent::reset() {
    lastRequestId_ = 0U;
    clearVehicleResponseTopic();
}
void VehicleResponseIntent::tick() {
    const uint64_t &currentVehicleRequestId {data::vehicleRequestTopic.requestId};
    if (currentVehicleRequestId != lastRequestId_) {
        // new packet arrived
        // Clear the output
        reset();
        lastRequestId_ = currentVehicleRequestId;
    }

    // Update output
    data::vehicleResponseTopic.tickCount++;
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::vehicleResponseTopic.wheelOdometry[i] =
          data::vehicleResponseTopic.wheelOdometry[i] + data::wheelOdometryTopic.wheelOdometry[i];
    }

    // Generate Output
    comm::GHPacket *packetPtr =
      reinterpret_cast<comm::GHPacket *>(data::vehicleResponseTopic.ghPacketBuffer);
    static int b {0};
    for (std::size_t i {0U}; i < 4U; ++i) {
        (packetPtr->odometry)[i] = data::vehicleResponseTopic.wheelOdometry[i].odometry;
    }
}

void VehicleResponseIntent::clearVehicleResponseTopic() {
    data::vehicleResponseTopic.tickCount = 0;
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::vehicleResponseTopic.wheelOdometry[i].qualifier = data::Qualifier::GOOD;
        data::vehicleResponseTopic.wheelOdometry[i].odometry  = 0;
    }
}
}    // namespace intents
}    // namespace cooboc