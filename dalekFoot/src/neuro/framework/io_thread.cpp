#include "framework/io_thread.h"
#include "framework/event_type.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

IOThread::IOThread(const ThreadHub &hub): IThread(hub) {

}

IOThread::~IOThread() {


}


void IOThread::work() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		cout << "IO thread" << endl;
	}
}


void IOThread::onNotify(uint64_t eventType) {
	switch (eventType) {
		case (EventType::GLOBAL_CYCLE_START) : {
			// output the data;
			printf("output data\r\n");
			break;
		}
		case (EventType::IO_MCU_RESPONSE_TIMEOUT) : {
			printf("response timeout\r\n");
			break;
		}
		default: {
			break;
		}
	}
}


