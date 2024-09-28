#include "intents/vehicle_response_intent/vehicle_response_intent.h"
#include <cstdint>
#include <cstring>
#include "data/gh_protocol.h"
#include "intents/common/data_pool.h"
#include "utils/math.h"

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
    // TODO: speed calculate
    data::vehicleResponseTopic.tickCount++;
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::vehicleResponseTopic.wheelOdometry[i] =
          data::vehicleResponseTopic.wheelOdometry[i] + data::wheelOdometryTopic.wheelOdometry[i];
    }

    // Generate Output
    comm::GHPacket txPacket {};
    txPacket.tickCount = data::vehicleResponseTopic.tickCount;

    for (std::size_t i {0U}; i < 4U; ++i) {
        txPacket.encoderOdometry[i] = data::vehicleResponseTopic.wheelOdometry[i].odometry;
    }
    std::uint32_t crc = utils::math::calculateCrc(txPacket);
    txPacket.crc      = crc;

    std::memcpy(reinterpret_cast<comm::GHPacket *>(data::vehicleResponseTopic.ghPacketBuffer),
                &txPacket,
                GH_PACKET_SIZE);
}

void VehicleResponseIntent::clearVehicleResponseTopic() {
    data::vehicleResponseTopic.tickCount = 0;
    for (std::size_t i {0U}; i < 4U; ++i) {
        data::vehicleResponseTopic.wheelOdometry[i].qualifier = data::Qualifier::GOOD;
        data::vehicleResponseTopic.wheelOdometry[i].odometry  = 0;
    }
    std::memset(data::vehicleResponseTopic.ghPacketBuffer, 0, GH_PACKET_SIZE);
}
}    // namespace intents
}    // namespace cooboc