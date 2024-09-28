#include "sil/simulator/simulator.h"
#include <cstdint>
#include "data/defs/vehicle_response.h"
#include "intents/topics/vehicle_request_topic.h"
#include "utils/math.h"

namespace cooboc {
namespace sil {

Simulator::Simulator() {}
Simulator::~Simulator() {}
void Simulator::setup() {
    for (std::size_t i {0U}; i < 4U; ++i) {
        vehicleWheelSpeed_[i]    = 0.0F;
        vehicleWheelOdometry_[i] = 0.0F;
    }
}
void Simulator::tick() {
    std::int32_t beginOdometry[4U] {0, 0, 0, 0};
    for (std::size_t i {0U}; i < 4U; ++i) {
        // Update each wheel speed
        beginOdometry[i]      = vehicleWheelOdometry_[i];
        vehicleWheelSpeed_[i] = vehicleRequestPacket_.wheelEncoderPlanning[i][0U];
        vehicleWheelOdometry_[i] += vehicleWheelSpeed_[i] * 0.01F;
    }

    // Write packet
    for (std::size_t i {0U}; i < 4U; ++i) {
        vehicleResponsePacket_.encoderOdometry[i] =
          static_cast<std::int32_t>(vehicleWheelOdometry_[i]);
        vehicleResponsePacket_.intervalOdometry[i] =
          static_cast<std::int32_t>(vehicleWheelOdometry_[i]) - beginOdometry[i];
    }
    vehicleResponsePacket_.tickCount = 5U;

    std::uint32_t crc          = utils::math::calculateCrc(vehicleResponsePacket_);
    vehicleResponsePacket_.crc = crc;
}


void Simulator::updateVehicleRequest(const comm::HGPacket &vehicleRequest) {
    vehicleRequestPacket_ = vehicleRequest;
}


}    // namespace sil

}    // namespace cooboc
