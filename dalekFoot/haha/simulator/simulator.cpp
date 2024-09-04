#include "simulator/simulator.h"
#include <cstdint>
#include "data/defs/vehicle_response.h"
#include "intents/topics/vehicle_request_topic.h"
#include "utils/math.h"

namespace cooboc {
namespace sim {

Simulator::Simulator() {}
Simulator::~Simulator() {}
void Simulator::tick() {}

void Simulator::updateVehicleRequest(const intent::VehicleRequestTopic &vehicleRequest) {
    for (std::size_t i {0U}; i < 4U; ++i) {
        // Update each wheel speed
        const float speed         = vehicleRequest.wheelControlPlanning[i].speed[0U];
        const float odometry      = speed * 0.01F;
        const int64_t encoderDiff = (odometry * 4096) / (utils::math::PI * 0.06);

        vehicleResponse_.wheelStatus[i].speed = speed;
        vehicleResponse_.wheelStatus[i].encoder += encoderDiff;
    }
    //
}


data::VehicleResponse Simulator::getVehicleResponse() {
    //

    return vehicleResponse_;
}

}    // namespace sim

}    // namespace cooboc
