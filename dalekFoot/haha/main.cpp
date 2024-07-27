#include <unistd.h>
#include <csignal>
#include <iostream>
#include "intents/intent_manager.h"


namespace {
volatile std::sig_atomic_t gSignalStatus = 0;    // nosignal
}


void signalHandler(int signum) { gSignalStatus = signum; }

int main(int argc, char *argv[], char **envs) {
    cooboc::intents::IntentManager intentManager;
    intentManager.setup();

    // Handle signal interrupt
    std::signal(SIGINT, signalHandler);

    // trigger by loop, simulate the time

    while (gSignalStatus != SIGINT) {}


    return 0;
}