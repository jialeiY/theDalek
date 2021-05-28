#include "framework/control_thread.h"
#include "framework/event_type.h"
#include "framework/entity_agency.h"
#include "module/sensing/i_sensor.h"
#include "action/power/power_action.h"
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
	std::vector<sensing::ISensor *> sensorList = mAgency.getSensorList();
	for (sensing::ISensor *sensor : sensorList) {
		sensor->setExchangeMemoryArea(&mSensorData);
	}
	std::vector<action::IAction *> actionList = mAgency.getActionList();
	for (auto *action : actionList) {
		LogInfo("set sensor data");
		action->setSensorData(&mSensorData);
		action->setExchangeMemoryArea(&mActionData);
	}
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	if (eventType == EventType::GLOBAL_CYCLE_START) {
		mCycleCount ++;
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
		

		
		// Initialize data area
		memset(&mSensorData, 0, sizeof(data_types::SensorData));
		memset(&mActionData, 0, sizeof(data_types::ActionData));

		// update all sensors
		std::vector<sensing::ISensor *> sensorList = mAgency.getSensorList();
		for (sensing::ISensor *sensor : sensorList) {
			sensor->updateFromSensor(mCycleCount, localData);
		}

		// 1. Odometry
		action::IAction *odometry = mAgency.getAction("odometry");
		odometry->execute();

		action::IAction *power = mAgency.getAction("power");
		power->execute();

		mStatus = ControlStatus::IDLE;
		notify("loop", EventType::CONTROL_FINISHED, nullptr);
	}
}


}

