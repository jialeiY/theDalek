#include "framework/thread/control/controller.h"
#include "module/data_types/hardware_data.h"
#include "module/sensing/i_sensor.h"
#include "framework/rtdp/logger/logger.h"
#include <cstring>
#include <vector>


namespace framework {
namespace thread {
namespace control {



Controller::Controller(const EntityAgency &agency): mAgency(agency),
																										mCycleCount(0ULL) {

}

Controller::~Controller() {

}

void Controller::init(void) {
	std::vector<sensing::ISensor *> sensorList = mAgency.getSensorList();
	for (sensing::ISensor *sensor : sensorList) {
		printf("ready to run the sensor module\r\n");
		sensor->setExchangeMemoryArea(&mSensorData);
	}
	std::vector<action::IAction *> actionList = mAgency.getActionList();
	for (auto *action : actionList) {
		LogInfo("set sensor data");
		action->setSensorData(&mSensorData);
		action->setExchangeMemoryArea(&mActionData);
	}
}


inline void Controller::beforeStep() {
	mCycleCount++;
	// Initialize data area
	memset(&mSensorData, 0, sizeof(data_types::SensorData));
	memset(&mActionData, 0, sizeof(data_types::ActionData));
}

void Controller::step(data_types::HardwareData *hardwareDataPtr) {
	beforeStep();

	// update all sensors
	std::vector<sensing::ISensor *> sensorList = mAgency.getSensorList();
	for (sensing::ISensor *sensor : sensorList) {
		sensor->updateFromSensor(mCycleCount, *hardwareDataPtr);
	}

	// 1. Odometry
	action::IAction *odometry = mAgency.getAction("odometry");
	odometry->execute(mCycleCount);

	action::IAction *power = mAgency.getAction("power");
	power->execute(mCycleCount);

	
	///TODO: OutputWriter needed
	// Compose output data
	hardwareDataPtr->output.value = mActionData.power.value;
	
}



}
}
}


