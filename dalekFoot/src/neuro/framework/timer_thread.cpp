#include "framework/timer_thread.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"

namespace framework {

TimerThread::TimerThread(const ThreadHub &hub) : 
	IThread(hub),
	mExchangeIdx(0U) {
}

TimerThread::~TimerThread() {
}

void TimerThread::onNotify(EventType eventType, volatile void *data) {
}

void TimerThread::work() {
	volatile void *ioBufferPtr;
	volatile void *controlBufferPtr;
	if (mExchangeIdx == 0) {
		ioBufferPtr = static_cast<volatile void *>(mExchange1);
		controlBufferPtr = static_cast<volatile void *>(mExchange2);
		mExchangeIdx = 1;
	} else {
		ioBufferPtr = static_cast<volatile void *>(mExchange2);
		controlBufferPtr = static_cast<volatile void *>(mExchange1);
		mExchangeIdx = 0;
	}

	notify("io", EventType::GLOBAL_CYCLE_START, ioBufferPtr);
	notify("control", EventType::GLOBAL_CYCLE_START, controlBufferPtr);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

}


}