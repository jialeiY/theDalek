#include <data/gh_protocol.h>
#include <unistd.h>
#include <csignal>
#include <iostream>
#include "data/defs/vehicle_response.h"
#include "intents/intent_manager.h"
#include "intents/topics/vehicle_request_topic.h"
#include "vehicle.h"

namespace {
volatile std::sig_atomic_t gSignalStatus = 0;    // nosignal
}


void signalHandler(int signum) { gSignalStatus = signum; }

int main(int argc, char *argv[], char **envs) {
    // TODO
    static_assert(sizeof(cooboc::comm::HGPacket) <= HG_PACKET_SIZE);
    static_assert(sizeof(cooboc::comm::GHPacket) < HG_PACKET_SIZE);


    std::printf("size of gh_protocol: %ld\r\n", sizeof(cooboc::comm::HGPacket));

    cooboc::intent::IntentManager intentManager;
    cooboc::vehicle::Vehicle vehicle;

    intentManager.setup();
    vehicle.setup();

    // Handle signal interrupt
    std::signal(SIGINT, signalHandler);

    // trigger by loop, simulate the time

    while (gSignalStatus != SIGINT) {
        // time source here


        intentManager.tick();

        // cooboc::comm::HGPacket

        // WIP
        const cooboc::intent::VehicleRequestTopic &vrt {intentManager.getVehicleRequest()};
        vehicle.setRequest(vrt);
        vehicle.tick();
        const cooboc::data::VehicleResponse vr {vehicle.getResponse()};

        // SIL
        // simulator.updateVehicleRequest(vrt);
        // simulator.tick();
        // const cooboc::data::VehicleResponse vr {simulator.getVehicleResponse()};


        // // HIL
        // const cooboc::intent::VehicleRequestTopic &vrt {intentManager.getVehicleRequest()};
        // spi.sendPacket(vrt);
        // const cooboc::data::VehicleResponse vr {spi.getVehicleResponse()};

        intentManager.updateVehicleResponse(vr);
    }


    return 0;
}