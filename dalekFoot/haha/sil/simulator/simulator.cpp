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
    for (std::size_t i {0U}; i < 4U; ++i) {
        // Update each wheel speed
        vehicleWheelSpeed_[i] = vehicleRequestPacket_.wheelsPlanning[i][0U];
        const float dist      = vehicleWheelSpeed_[i] * 0.01F;
        // const int64_t encoderDiff = (odometry * 4096) / (utils::math::PI * 0.06);
        vehicleWheelOdometry_[i] += dist;
    }

    // Write packet
    for (std::size_t i {0U}; i < 4U; ++i) {
        vehicleResponsePacket_.wheelOdometry[i] = vehicleWheelOdometry_[i];
        vehicleResponsePacket_.wheelSpeed[i]    = vehicleWheelSpeed_[i];
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
