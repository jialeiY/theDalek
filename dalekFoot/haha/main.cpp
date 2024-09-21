#include <data/gh_protocol.h>
#include <unistd.h>
#include <csignal>
#include <iostream>
#include "data/defs/vehicle_response.h"
#include "intents/intent_manager.h"
#include "intents/topics/vehicle_request_topic.h"
#include "simulator/simulator.h"

namespace {
volatile std::sig_atomic_t gSignalStatus = 0;    // nosignal
}


void signalHandler(int signum) { gSignalStatus = signum; }

int main(int argc, char *argv[], char **envs) {
    // TODO
    static_assert(sizeof(cooboc::comm::HGPacket) < HG_PACKET_SIZE);
    static_assert(sizeof(cooboc::comm::GHPacket) < HG_PACKET_SIZE);


    std::printf("size of gh_protocol: %ld\r\n", sizeof(cooboc::comm::HGPacket));
    while (true) {}
    cooboc::intent::IntentManager intentManager;
    cooboc::sim::Simulator simulator;
    intentManager.setup();
    simulator.setup();

    // Handle signal interrupt
    std::signal(SIGINT, signalHandler);

    // trigger by loop, simulate the time

    while (gSignalStatus != SIGINT) {
        intentManager.tick();

        // TODO
        // VehicleControlCommand &vcc = intentManager.getVehicleControlCommand();
        // simulator.setVehicleControlCommand(vcc);

        const cooboc::intent::VehicleRequestTopic &vrt {intentManager.getVehicleRequest()};
        simulator.updateVehicleRequest(vrt);
        simulator.tick();


        // usleep(10000ULL);
        const cooboc::data::VehicleResponse vr {simulator.getVehicleResponse()};
        intentManager.updateVehicleResponse(vr);
    }


    return 0;
}