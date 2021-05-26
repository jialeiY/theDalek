#include "framework/loop_thread.h"
#include "parameter.h"
#include "logger/logger.h"
#include "framework/event_type.h"
#include "module/mem/mem.h"
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

static void evaluateOutputData(volatile data_types::ExchangeArea* exchangeArea) {
	/// TODO: if output data not valid, set to zero
}

static inline void resetInputData(volatile data_types::ExchangeArea* exchangeArea) {
	mem::memset(&(exchangeArea->input), sizeof(exchangeArea->input), 0U);
}

static inline void resetOutputData(volatile data_types::ExchangeArea *exchangeArea) {
	mem::memset(&(exchangeArea->output), sizeof(exchangeArea->output), 0U);
}

namespace framework {
LoopThread::LoopThread(const ThreadHub &hub) : 
	IThread(hub),
	mStatus(WAITTING),
	mCycleStartTime(0ULL),
	mInputExchangeIdx(0U),
	mWheel() {

	//Initialize memory
	mem::memset(&mExchange1, sizeof(struct data_types::ExchangeArea), 0U);
	mem::memset(&mExchange2, sizeof(struct data_types::ExchangeArea), 0U);
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

	// Step 1. Check timeout
	if ((currentTime - mCycleStartTime) > kLoopThreadInputTimeout) {
		LogError("timeout, TODO: do the degradation for sensor");
		switchToWaitting(currentTime);
	} else {
		mWheel.tick();
		if (mWheel.hasResult()) {
			switchToWaitting(currentTime);
		}
	}
}



/// @brief tick function for waitting period
void LoopThread::tickOnWaitting(const std::uint64_t &currentTime) {
	if ((currentTime - mCycleStartTime) > kLoopThreadInterval) {
		switchToWorking(currentTime);
	}
}

/// @brief This function is used to switching the status of LoopThread. After 
/// Swtich it should notify control thread to start colculation
void LoopThread::switchToWorking(const std::uint64_t &currentTime) {
	// Reset the time
	mCycleStartTime = currentTime;
	// Switch the working status
	mStatus = LoopStatus::WORKING;

	
	
	volatile struct data_types::ExchangeArea *inputBufferPtr = mInputExchangeIdx == 0 ? &mExchange1 : &mExchange2;
	volatile struct data_types::ExchangeArea *outputBufferPtr = mInputExchangeIdx == 0 ? &mExchange2 : &mExchange1;
	notify("control", EventType::GLOBAL_CYCLE_START, outputBufferPtr);
	mWheel.startCycle(inputBufferPtr);
	
	
}


void LoopThread::switchToWaitting(const std::uint64_t &currentTime) {
	mWheel.endCycle();
	mStatus = LoopStatus::WAITTING;
	
	/// TODO: Check 1. If the transmitting is finished
	/// 2. If the contorl calculation finished
	/// 3. If time is up.

	/// 4. If the condition reached. prepare the output for transmitting.
	/// TODO: Check the output, if the output is not produced by controlThread, 
	/// 
	// Evaluation Input and Output, Set the area to all-zero. if invalid
	volatile data_types::ExchangeArea *inputBufferPtr = (mInputExchangeIdx == 0 ? &mExchange1 : &mExchange2);
	volatile data_types::ExchangeArea *outputBufferPtr = (mInputExchangeIdx == 0 ? &mExchange2 : &mExchange1);

	
	resetOutputData(inputBufferPtr);
	evaluateOutputData(outputBufferPtr);
	
	// switch exchangeArea Index
	mInputExchangeIdx = 1U - mInputExchangeIdx;
}


}