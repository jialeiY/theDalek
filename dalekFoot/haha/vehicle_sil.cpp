#include <cstdio>
#include "simulator/simulator.h"
#include "vehicle.h"

namespace cooboc {
namespace vehicle {

namespace {
cooboc::sim::Simulator simulator_;
cooboc::intent::VehicleRequestTopic vehicleRequestTopic_ {};
cooboc::data::VehicleResponse vehicleResponse_ {};
}    // namespace

void Vehicle::setup() { simulator_.setup(); }
void Vehicle::setRequest(const cooboc::intent::VehicleRequestTopic &vehicleRequestTopic) {
    vehicleRequestTopic_ = vehicleRequestTopic;
}
void Vehicle::tick() {
    std::printf("sil tick\r\n");
    simulator_.updateVehicleRequest(vehicleRequestTopic_);
    simulator_.tick();
    vehicleResponse_ = simulator_.getVehicleResponse();
}

cooboc::data::VehicleResponse Vehicle::getResponse() { return vehicleResponse_; }
}    // namespace vehicle
}    // namespace cooboc