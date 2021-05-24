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
	volatile data_types::ExchangeArea *ioBufferPtr;
	volatile data_types::ExchangeArea *controlBufferPtr;
	if (mExchangeIdx == 0) {
		ioBufferPtr = &mExchange1;
		controlBufferPtr = &mExchange2;
		mExchangeIdx = 1;
	} else {
		ioBufferPtr = &mExchange2;
		controlBufferPtr = &mExchange1;
		mExchangeIdx = 0;
	}

	notify("io", EventType::GLOBAL_CYCLE_START, ioBufferPtr);
	notify("control", EventType::GLOBAL_CYCLE_START, controlBufferPtr);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

}


}