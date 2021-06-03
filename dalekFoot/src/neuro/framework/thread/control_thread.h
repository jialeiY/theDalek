#ifndef __FRAMEWORK_THREAD_CONTROL_THREAD_H__
#define __FRAMEWORK_THREAD_CONTROL_THREAD_H__

#include "framework/thread/i_thread.h"
#include "framework/thread/entity_agency.h"
#include "module/data_types/hardware_data.h"
#include "module/data_types/sensor_data.h"
#include "module/data_types/action_data.h"
#include <cstdint>

namespace framework {
namespace thread {

class ControlThread : public IThread {
	public:
		ControlThread(const ThreadHub &hub, const EntityAgency &agency);
		virtual ~ControlThread();
		virtual void init();
	protected:
		virtual void onNotify(EventType msgType, volatile void *data=nullptr);

	private:
		enum ControlStatus {
			IDLE,
			WORKING
		};
		virtual void work();
		volatile data_types::HardwareData *mHardwareDataPtr;
		const EntityAgency &mAgency;
		ControlStatus mStatus;
		volatile void *mWorkingDataPtr;
		data_types::SensorData mSensorData;
		data_types::ActionData mActionData;
		uint64_t mCycleCount;
};

}
}

#endif
