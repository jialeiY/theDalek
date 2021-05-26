#include "framework/control_thread.h"
#include "framework/event_type.h"
#include "framework/entity_agency.h"
#include "hardware/i_hardware.h"
#include "action/odometry/odometry_action.h"
#include "logger/logger.h"
#include "module/mem/mem.h"
#include <vector>

namespace framework {


ControlThread::ControlThread(const ThreadHub &hub, const EntityAgency &agency) : 
	IThread(hub), 
	mExchangeAreaPtr(nullptr),
	mAgency(agency),
	mStatus(IDLE),
	mWorkingDataPtr(nullptr) {
}

ControlThread::~ControlThread() {
}

void ControlThread::onNotify(EventType eventType, volatile void *data) {
	if (eventType == EventType::GLOBAL_CYCLE_START) {
		mStatus = ControlStatus::WORKING;
		mWorkingDataPtr = data;
	}
}

void ControlThread::work() {
	if (mStatus == ControlStatus::WORKING) {
		mExchangeAreaPtr = static_cast<volatile data_types::ExchangeArea *>(mWorkingDataPtr);
		// copy to local memory
		data_types::ExchangeArea localData;
		mem::memcpy(&localData, mExchangeAreaPtr, sizeof(struct data_types::ExchangeArea));
		
		// update all sensors
		std::vector<hardware::IHardware *> hardwareList = mAgency.getHardwareList();
		for (hardware::IHardware *hardware : hardwareList) {
			hardware->updateFromSensor(localData);
		}


		// 1. Odometry
		action::IAction *odometry = mAgency.getAction("odometry");
		odometry->execute();

		mStatus = ControlStatus::IDLE;
		notify("timer", EventType::CONTROL_FINISHED, nullptr);		
		LogDebug("control thread");
	}
}


}

