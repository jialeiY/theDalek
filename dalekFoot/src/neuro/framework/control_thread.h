#ifndef __FRAMEWORK_CONTROL_THREAD_H__
#define __FRAMEWORK_CONTROL_THREAD_H__

#include "framework/i_thread.h"
#include "module/data_types/exchange_area.h"

namespace framework {

class ControlThread : public IThread {
	public:
		ControlThread(const ThreadHub &hub);
		virtual ~ControlThread();

	protected:
		virtual void onNotify(EventType msgType, volatile void *data=nullptr);

	private:
		virtual void work();
		volatile data_types::ExchangeArea *mExchangeAreaPtr;
};

}


#endif
