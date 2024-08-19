#include "simulator/simulator.h"
#include "data/defs/vehicle_response.h"
#include "intents/topics/vehicle_request_topic.h"

namespace cooboc {
namespace sim {

Simulator::Simulator() {}
Simulator::~Simulator() {}
void Simulator::tick() { vehicleResponse_.wheelStatus[0].speed += 0.1F; }

void Simulator::updateVehicleRequest(const intent::VehicleRequestTopic &vehicleRequest) {
    //
}


data::VehicleResponse Simulator::getVehicleResponse() {
    //

    return vehicleResponse_;
}

}    // namespace sim

}    // namespace cooboc
