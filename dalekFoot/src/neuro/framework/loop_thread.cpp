#include "framework/loop_thread.h"
#include "parameter.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>

namespace framework {
LoopThread::LoopThread(const ThreadHub &hub) : 
	IThread(hub) {

}

LoopThread::~LoopThread() {

}

void LoopThread::onNotify(EventType msgType, volatile void *data) {

}

/// @brief This is the main loop controller to contorl the time interval of 
/// sensring and control calculation. 
/// work() function intented to return fast to not block the IO. and not block
/// being notified.
void LoopThread::work() {
	LogInfo("work");
	std::this_thread::sleep_for(std::chrono::nanoseconds(kLoopThreadInterval));
}


}