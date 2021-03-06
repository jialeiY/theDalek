#ifndef __FRAMEWORK_THREAD_LOOP_THREAD_H__
#define __FRAMEWORK_THREAD_LOOP_THREAD_H__

#include "framework/thread/i_thread.h"
#include "module/data_types/hardware_data.h"
#include "module/hardware/usart/wheel_usart.h"
#include <cstdint>

namespace framework {
namespace thread {

class LoopThread : public IThread {
	public:
		LoopThread(const ThreadHub &hub);
		virtual ~LoopThread();
		
	protected:
		virtual void onNotify(EventType msgType, volatile void *data = nullptr);
		virtual void work();
	private:
		enum LoopStatus {
			WORKING,
			WAITTING
		};
		LoopStatus mStatus;
		std::uint64_t mCycleStartTime;
		bool mIsIoFinished;
		bool mIsControlFinished;

		/// @brief The memory area used for exchange data from input and output.
		volatile struct data_types::HardwareData mExchange1;
		volatile struct data_types::HardwareData mExchange2;
		/// @brief The variable to indicate which exchange area is used
		uint8_t mIOExchangeIdx;

		hardware::usart::WheelUsart mWheelUsart;

		void tickOnWaitting(const std::uint64_t &currentTime);
		void tickOnWorking(const std::uint64_t &currentTime);

		void switchToWorking(const std::uint64_t &currentTime);
		void switchToWaitting(const std::uint64_t &currentTime);

		inline volatile data_types::HardwareData *getIoBufferPtr() {
			return mIOExchangeIdx == 0 ? &mExchange1 : &mExchange2;
		} 
		inline volatile data_types::HardwareData *getControlBufferPtr() {
			return mIOExchangeIdx == 0 ? &mExchange2 : &mExchange1;
		}
};

}
}

#endif

