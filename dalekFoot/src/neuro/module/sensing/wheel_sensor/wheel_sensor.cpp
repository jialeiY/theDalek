#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "module/data_types/exchange_area.h"
#include "logger/logger.h"
namespace sensing {
namespace wheel_sensor {

WheelSensor::WheelSensor(const std::string &name, framework::EntityAgency &entityAgency) :
	ISensor(name, entityAgency) {

}

WheelSensor::~WheelSensor() {
	
}


void WheelSensor::updateFromSensor(const data_types::ExchangeArea &inputData) {
	for (int i=0; i<4; ++i) {
		mStatus.encoder[i] = inputData.input.mcuSensors.motorEncoder[i];
	}

	// LogInfo("on notifiy of contorl: %x", mExchangeAreaPtr);
	LogInfo("wheel: %d %d %d %d", 
		mStatus.encoder[0],
		mStatus.encoder[1],
		mStatus.encoder[2],
		mStatus.encoder[3]);
}


sensing::WheelStatus WheelSensor::getWheelStatus(void) const {
	return mStatus;
}

}
}