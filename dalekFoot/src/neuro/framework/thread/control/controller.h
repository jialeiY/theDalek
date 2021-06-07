#ifndef __FRAMEWORK_THREAD_CONTROL_CONTROLLER_H__
#define __FRAMEWORK_THREAD_CONTROL_CONTROLLER_H__

#include "module/data_types/hardware_data.h"
#include "framework/thread/entity_agency.h"
#include "module/data_types/sensor_data.h"
#include "module/data_types/action_data.h"

namespace framework {
namespace thread {
namespace control {

class Controller {
	public:
		Controller(const EntityAgency &agency);
		virtual ~Controller();
		void init();
		void beforeStep(void);
		void step(data_types::HardwareData *hardwareDataPtr);
	private:
		const EntityAgency &mAgency;
		uint64_t mCycleCount;
		data_types::SensorData mSensorData;
		data_types::ActionData mActionData;
};


}
}
}


#endif


