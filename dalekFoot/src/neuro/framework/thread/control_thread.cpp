#include "framework/thread/control_thread.h"
#include "framework/thread/event_type.h"
#include "framework/thread/entity_agency.h"
#include "framework/thread/control/controller.h"
#include "action/power/power_action.h"
#include "action/odometry/odometry_action.h"
#include "framework/rtdp/persistent/writer_handler.h"
#include "framework/rtdp/logger/logger.h"
#include "module/mem/mem.h"


namespace framework {
namespace thread {

ControlThread::ControlThread(const ThreadHub &hub, const EntityAgency &agency) : 
	IThread(hub), 
	mController(agency),
	mStatus(IDLE),
	mWorkingDataPtr(nullptr) {
}

ControlThread::~ControlThread() {

}

void ControlThread::init() {
	mController.init();
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	if (eventType == EventType::GLOBAL_CYCLE_START) {
		mStatus = ControlStatus::WORKING;
		mWorkingDataPtr = data;
	}
}

void ControlThread::work() {
	if (mStatus == ControlStatus::WORKING) {
		volatile data_types::HardwareData *hardwareDataPtr = static_cast<volatile data_types::HardwareData *>(mWorkingDataPtr);
		
		// copy to local memory
		data_types::HardwareData localData;
		mem::memcpy(&localData, hardwareDataPtr, sizeof(struct data_types::HardwareData));
		WritePersistentHardwareData(&localData);

		mController.step(&localData);
		// Write Output back to exchagne area
		mem::memcpy(hardwareDataPtr, &localData, sizeof(struct data_types::HardwareData));


		mStatus = ControlStatus::IDLE;
		notify("loop", EventType::CONTROL_FINISHED, nullptr);
	}
}


}
}
