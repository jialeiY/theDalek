#include "framework/watchdog_thread.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

WatchdogThread::WatchdogThread(const ThreadHub &hub): IThread(hub) {

}

WatchdogThread::~WatchdogThread() {

}

void WatchdogThread::onNotify(uint64_t msgType) {
	cout << "got notify in watchdog" << msgType << endl;
}




void WatchdogThread::work() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "out" << endl;
	}
}


