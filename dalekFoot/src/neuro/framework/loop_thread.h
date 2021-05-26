#ifndef __FRAMEWORK_LOOP_THREAD_H__
#define __FRAMEWORK_LOOP_THREAD_H__

#include "framework/i_thread.h"
#include "module/data_types/exchange_area.h"
#include "module/hardware/usart/wheel_usart.h"
#include <cstdint>

namespace framework {

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
		/// @brief The memory area used for exchange data from input and output.
		volatile struct data_types::ExchangeArea mExchange1;
		volatile struct data_types::ExchangeArea mExchange2;
		/// @brief The variable to indicate which exchange area is used
		uint8_t mInputExchangeIdx;

		hardware::usart::WheelUsart mWheel;

		void tickOnWaitting(const std::uint64_t &currentTime);
		void tickOnWorking(const std::uint64_t &currentTime);

		void switchToWorking(const std::uint64_t &currentTime);
		void switchToWaitting(const std::uint64_t &currentTime);
};

}

#endif

