#include "framework/timer_thread.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"
#include <stdint.h>

namespace framework {

TimerThread::TimerThread(const ThreadHub &hub) : 
	IThread(hub),
	mExchangeIdx(0U) {
		for (size_t i=0; i<sizeof(struct data_types::ExchangeArea); ++i) {
			mExchange1[i] = 0;
		}
		for (size_t i=0; i<sizeof(struct data_types::ExchangeArea); ++i) {
			mExchange2[i] = 0;
		}

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