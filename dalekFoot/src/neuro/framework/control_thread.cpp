#include "framework/control_thread.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"

namespace framework {


ControlThread::ControlThread(const ThreadHub &hub) : IThread(hub) {
}

ControlThread::~ControlThread() {
}

void ControlThread::onNotify(EventType eventType, void *data) {
	
}

void ControlThread::work() {
	
}


}

