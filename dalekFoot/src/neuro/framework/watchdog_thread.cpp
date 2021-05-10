#include "framework/watchdog_thread.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"


using namespace std;

WatchdogThread::WatchdogThread(const ThreadHub &hub): IThread(hub) {

}

WatchdogThread::~WatchdogThread() {

}

void WatchdogThread::onNotify(uint64_t eventType) {
	cout << "got notify in watchdog" << eventType << endl;
}




void WatchdogThread::work() {
	notify("io", EventType::GLOBAL_CYCLE_START);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	notify("io", EventType::IO_MCU_RESPONSE_TIMEOUT);
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}


