#ifndef __FRAMEWORK_CONTROL_THREAD_H__
#define __FRAMEWORK_CONTROL_THREAD_H__

#include "framework/i_thread.h"
#include "module/data_types/exchange_area.h"
#include "framework/entity_agency.h"

namespace framework {

class ControlThread : public IThread {
	public:
		ControlThread(const ThreadHub &hub, const EntityAgency &agency);
		virtual ~ControlThread();

	protected:
		virtual void onNotify(EventType msgType, volatile void *data=nullptr);

	private:
		virtual void work();
		volatile data_types::ExchangeArea *mExchangeAreaPtr;
		const EntityAgency &mAgency;
};

}


#endif
