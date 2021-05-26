#include "framework/loop_thread.h"

namespace framework {
LoopThread::LoopThread(const ThreadHub &hub) : 
	IThread(hub) {

}

LoopThread::~LoopThread() {

}

void LoopThread::onNotify(EventType msgType, volatile void *data) {

}


void LoopThread::work() {

}


}