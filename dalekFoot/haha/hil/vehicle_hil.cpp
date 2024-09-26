#include <cstdio>
#include "hil/spi_driver/spi_driver.h"
#include "vehicle.h"

namespace cooboc {
namespace vehicle {

namespace {
constexpr char devicePath[] {"/dev/ch34x_pis1"};
cooboc::hil::Ch341 ch341_ {devicePath};
cooboc::intent::VehicleRequestTopic vehicleRequestTopic_ {};
cooboc::data::VehicleResponse vehicleResponse_ {};
}    // namespace

void Vehicle::setup() { ch341_.setup(); }

void Vehicle::setRequest(const cooboc::intent::VehicleRequestTopic &vehicleRequestTopic) {
    vehicleRequestTopic_ = vehicleRequestTopic;
}

void Vehicle::tick() {
    std::printf("hil tick\r\n");
    ch341_.sendPacket(vehicleRequestTopic_);
}

cooboc::data::VehicleResponse Vehicle::getResponse() {}
}    // namespace vehicle
}    // namespace cooboc