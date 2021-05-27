#include "framework/loop_thread.h"
#include "parameter.h"
#include "logger/logger.h"
#include "framework/event_type.h"
#include "module/mem/mem.h"
#include "module/time/time.h"
#include <chrono>
#include <thread>


static void evaluateOutputData(volatile data_types::HardwareData* hardwareData) {
	/// TODO: if output data not valid, set to zero
}

static inline void resetInputData(volatile data_types::HardwareData* hardwareData) {
	mem::memset(&(hardwareData->input), sizeof(hardwareData->input), 0U);
}

static inline void resetOutputData(volatile data_types::HardwareData *hardwareData) {
	mem::memset(&(hardwareData->output), sizeof(hardwareData->output), 0U);
}

namespace framework {
LoopThread::LoopThread(const ThreadHub &hub) : 
	IThread(hub),
	mStatus(WAITTING),
	mCycleStartTime(0ULL),
	mIsIoFinished(false),
	mIsControlFinished(false),
	mInputExchangeIdx(0U),
	mWheel() {

	//Initialize memory
	mem::memset(&mExchange1, sizeof(struct data_types::HardwareData), 0U);
	mem::memset(&mExchange2, sizeof(struct data_types::HardwareData), 0U);
	LogInfo("Program started");
}

LoopThread::~LoopThread() {

}


void LoopThread::onNotify(EventType msgType, volatile void *data) {
	if (msgType == EventType::CONTROL_FINISHED) {
		mIsControlFinished = true;
		LogInfo("control time duration: %lu", times::useconds() - mCycleStartTime);
	}
	

}

/// @brief This is the main loop controller to contorl the time interval of 
/// sensring and control calculation. 
/// work() function intented to return fast to not block the IO. and not block
/// being notified.
void LoopThread::work() {
	std::uint64_t currentTime = times::useconds();
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
		LogWarn("TODO: timeout");
		switchToWaitting(currentTime);
	} else {
		if (!mIsIoFinished) {
			mWheel.tick();
			if (mWheel.hasResult()) {
				mWheel.endCycle();
				mIsIoFinished = true;
				LogInfo("io time duration: %lu", currentTime - mCycleStartTime);
			}
		}
		if (mIsControlFinished && mIsIoFinished) {
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
	mIsIoFinished = false;
	mIsControlFinished = false;	
	
	volatile struct data_types::HardwareData *inputBufferPtr = mInputExchangeIdx == 0 ? &mExchange1 : &mExchange2;
	volatile struct data_types::HardwareData *outputBufferPtr = mInputExchangeIdx == 0 ? &mExchange2 : &mExchange1;
	outputBufferPtr->cycleStartTime = mCycleStartTime;
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
	volatile data_types::HardwareData *inputBufferPtr = (mInputExchangeIdx == 0 ? &mExchange1 : &mExchange2);
	volatile data_types::HardwareData *outputBufferPtr = (mInputExchangeIdx == 0 ? &mExchange2 : &mExchange1);

	
	resetOutputData(inputBufferPtr);
	/// TODO: evalutate the output after calculation
	// evaluateOutputData(outputBufferPtr);
	
	// switch HardwareData Index
	mInputExchangeIdx = 1U - mInputExchangeIdx;
}


}