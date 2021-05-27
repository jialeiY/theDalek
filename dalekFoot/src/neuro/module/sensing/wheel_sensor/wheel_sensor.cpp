#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "module/data_types/hardware_data.h"
#include "logger/logger.h"
#include "parameter.h"
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

WheelSensor::WheelSensor(const std::string &name, framework::EntityAgency &entityAgency) :
	ISensor(name, entityAgency) {

}

WheelSensor::~WheelSensor() {
	
}


void WheelSensor::updateFromSensor(std::uint64_t cycleCount, const data_types::HardwareData &inputData) {
	// Step 1. Update encoder history
	for (int i=0; i<(kWheelSensorHistorySize-1); ++i) {
		for (int j=0; j<4; ++j) {
			mHwEncoder[i][j] = mHwEncoder[i+1][j];
		}
	}
	for (int i=0; i<4; ++i) {
		mHwEncoder[(kWheelSensorHistorySize-1)][i] = inputData.input.mcuSensors.motorEncoder[i];
	}

	// Only start calculate after 5th cycle
	if (cycleCount > 5) {
		// Update Encoder
		for (int i=0; i<4; ++i) {
			mWheelData[i].encoder += mHwEncoder[(kWheelSensorHistorySize-1)][i] - mHwEncoder[(kWheelSensorHistorySize-2)][i];
		}
	}

	// Write to output
	std::string output;
	LogInfo("encoder: %d %d %d %d %d %d %d %d", 
		mWheelData[0].encoder, 
		mWheelData[1].encoder, 
		mWheelData[2].encoder, 
		mWheelData[3].encoder,
		mHwEncoder[(kWheelSensorHistorySize-1)][0],
		mHwEncoder[(kWheelSensorHistorySize-1)][1],
		mHwEncoder[(kWheelSensorHistorySize-1)][2],
		mHwEncoder[(kWheelSensorHistorySize-1)][3]);
}

void WheelSensor::warmupWork(const data_types::HardwareData &inputData) {

}


}
}