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
    virtual void work();
		volatile data_types::ExchangeArea mExchange1;
		volatile data_types::ExchangeArea mExchange2;
		uint8_t mExchangeIdx;
		
		
};


}

#endif
