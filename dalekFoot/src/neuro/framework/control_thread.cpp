#include "framework/control_thread.h"
#include "framework/event_type.h"
#include "logger/logger.h"
namespace framework {


ControlThread::ControlThread(const ThreadHub &hub) : IThread(hub) {
}

ControlThread::~ControlThread() {
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	
}

void ControlThread::work() {
	
}


}

