#include "sil/vehicle_sil.h"
#include <cstdio>
#include "data/gh_protocol.h"
#include "simulator/simulator.h"

namespace cooboc {
namespace vehicle {

namespace {
cooboc::sil::Simulator simulator_;


}    // namespace

void Vehicle::setup() { simulator_.setup(); }

void Vehicle::setRequest(const comm::HGPacket &hgPacket) {
    std::printf("sil tick\r\n");
    simulator_.updateVehicleRequest(hgPacket);
    simulator_.tick();
}
cooboc::comm::GHPacket Vehicle::getResponse() { return simulator_.getVehicleResponse(); }


void Vehicle::tick() {}


}    // namespace vehicle
}    // namespace cooboc