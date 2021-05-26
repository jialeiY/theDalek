#include "framework/loop_thread.h"

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
	
}


}