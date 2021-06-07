#ifndef __FRAMEWORK_THREAD_CONTROL_THREAD_H__
#define __FRAMEWORK_THREAD_CONTROL_THREAD_H__

#include "framework/thread/i_thread.h"
#include "framework/thread/entity_agency.h"
#include "framework/thread/control/controller.h"
#include "module/data_types/hardware_data.h"
#include <cstdint>

namespace framework {
namespace thread {

class ControlThread : public IThread {
	public:
		ControlThread(const ThreadHub &hub, const EntityAgency &agency);
		virtual ~ControlThread();
		virtual void init() override;
	protected:
		virtual void onNotify(EventType msgType, volatile void *data=nullptr) override;

	private:
		enum ControlStatus {
			IDLE,
			WORKING
		};
		virtual void work() override;
		
		framework::thread::control::Controller mController;
		ControlStatus mStatus;
		volatile void *mWorkingDataPtr;
};

}
}

#endif
