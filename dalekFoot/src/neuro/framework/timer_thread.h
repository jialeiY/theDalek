#ifndef __FRAMEWORK_TIMEER_THREAD_H__
#define __FRAMEWORK_TIMEER_THREAD_H__

#include "framework/i_thread.h"
#include "framework/event_type.h"
#include "module/data_types/exchange_area.h"
#include <stdint.h>

namespace framework {

class TimerThread : public IThread {
	public:
    TimerThread(const ThreadHub &hub);
    virtual ~TimerThread();

	protected:
    virtual void onNotify(EventType eventType, volatile void *data=nullptr);

	private:

		enum TimerStatus {
			NOT_STARTED,
			WAITTING_THREAD,
			WAITTING_CYCLE_FINISH
		};
    virtual void work();
		volatile uint8_t mExchange1[sizeof(struct data_types::ExchangeArea)];
		volatile uint8_t mExchange2[sizeof(struct data_types::ExchangeArea)];
		uint8_t mExchangeIdx;

		TimerStatus mStatus;
		bool mIsIoFinished;
		bool mIsControlFinished;
		uint64_t mGlobalCycleStartTime;
		
		
};


}

#endif
