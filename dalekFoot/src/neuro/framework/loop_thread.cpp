#include "framework/loop_thread.h"
#include "parameter.h"
#include "logger/logger.h"
#include <chrono>
#include <thread>

#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

static uint64_t useconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<uint64_t>(tv.tv_usec) + static_cast<uint64_t>(tv.tv_sec) * 1000000ULL;
}

namespace framework {
LoopThread::LoopThread(const ThreadHub &hub) : 
	IThread(hub),
	mStatus(WAITTING),
	mCycleStartTime(0ULL) {
		LogInfo("Program started");
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
	std::uint64_t currentTime = useconds();
	switch (mStatus) {
		case (WORKING): {
			tickOnWorking(currentTime);
			break;
		}
		case (WAITTING): {
			tickOnWaitting(currentTime);
			break;
		}
	}
	//std::this_thread::sleep_for(std::chrono::microseconds(kLoopThreadInterval));
}



/// @brief This function is the entry when the LoopThread under working status.
void LoopThread::tickOnWorking(const std::uint64_t &currentTime) {
	// for testing, change status to waitting immedately
	LogInfo("work");
	mStatus = LoopStatus::WAITTING;
}



/// @brief tick function for waitting period
void LoopThread::tickOnWaitting(const std::uint64_t &currentTime) {
	if ((currentTime - mCycleStartTime) > kLoopThreadInterval) {
		mCycleStartTime = currentTime;
		mStatus = LoopStatus::WORKING;
	}
}



}