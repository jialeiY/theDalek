#include "framework/control_thread.h"
#include "framework/event_type.h"
#include "framework/entity_agency.h"
#include "module/sensing/i_sensor.h"
#include "action/odometry/odometry_action.h"
#include "logger/logger.h"
#include "module/mem/mem.h"
#include <vector>

namespace framework {


ControlThread::ControlThread(const ThreadHub &hub, const EntityAgency &agency) : 
	IThread(hub), 
	mHardwareDataPtr(nullptr),
	mAgency(agency),
	mStatus(IDLE),
	mWorkingDataPtr(nullptr),
	mCycleCount(0ULL) {
}

ControlThread::~ControlThread() {

}

void ControlThread::init() {
	std::vector<action::IAction *> actionList = mAgency.getActionList();
	for (auto *action : actionList) {
		action->setMemoryArea(&mActionData);
	}
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	if (eventType == EventType::GLOBAL_CYCLE_START) {
		mStatus = ControlStatus::WORKING;
		mWorkingDataPtr = data;
	}
}

void ControlThread::work() {	
	if (mStatus == ControlStatus::WORKING) {
		mHardwareDataPtr = static_cast<volatile data_types::HardwareData *>(mWorkingDataPtr);
		// copy to local memory
		data_types::HardwareData localData;
		mem::memcpy(&localData, mHardwareDataPtr, sizeof(struct data_types::HardwareData));
		
		// update all sensors
		std::vector<sensing::ISensor *> hardwareList = mAgency.getSensorList();
		for (sensing::ISensor *hardware : hardwareList) {
			hardware->updateFromSensor(localData);
		}

		// Initialize data area
		memset(&mActionData, 0, sizeof(data_types::ActionData));


		// 1. Odometry
		action::IAction *odometry = mAgency.getAction("odometry");
		odometry->execute();

		mStatus = ControlStatus::IDLE;
		notify("loop", EventType::CONTROL_FINISHED, nullptr);
	}
}


}

