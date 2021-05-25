#include "framework/timer_thread.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "framework/event_type.h"
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

static uint64_t useconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec + (uint64_t)(tv.tv_sec * 1000000ULL);
}

namespace framework {

TimerThread::TimerThread(const ThreadHub &hub) : 
	IThread(hub),
	mIsIoFinished(false),
	mIsControlFinished(false),
	mExchangeIdx(0U),
	mStatus(TimerStatus::NOT_STARTED),
	mGlobalCycleStartTime(0ULL) {
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
	if (eventType == IO_FINISHED) {
		mIsIoFinished = true;
	} else  {
		if (eventType == CONTROL_FINISHED) {
			mIsControlFinished = true;
		}
	}
}

void TimerThread::work() {
	uint64_t currentTime = useconds();
	switch (mStatus) {
		case (NOT_STARTED): {
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
			mGlobalCycleStartTime = currentTime;
			mIsIoFinished = false;
			mIsControlFinished = false;
			mStatus = TimerStatus::WAITTING_THREAD;
			break;
		}
		case (WAITTING_THREAD): {
			if (mIsControlFinished && mIsIoFinished) {
				// Change status to end
				mStatus = TimerStatus::WAITTING_CYCLE_FINISH;
				LogInfo(" two thread finished");
				mStatus = TimerStatus::WAITTING_CYCLE_FINISH;
			}
			/// TODO: check if current time is timeout
			break;
		}
		case (WAITTING_CYCLE_FINISH): {
			if (currentTime - mGlobalCycleStartTime	> 2000000) {
				mStatus = NOT_STARTED;
			}
			break;
		}
		
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}


}