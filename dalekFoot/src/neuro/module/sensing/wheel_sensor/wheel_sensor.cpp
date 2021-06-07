#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "module/data_types/hardware_data.h"
#include "framework/rtdp/logger/logger.h"
#include "parameter.h"
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

WheelSensor::WheelSensor(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	ISensor(name, entityAgency) {

}

WheelSensor::~WheelSensor() {
	
}


void WheelSensor::updateFromSensor(const std::uint64_t cycleCount, const data_types::HardwareData &inputData) {
	// Validate
	
	const data_types::Qualifier & qualifier = inputData.input.mcuSensors.qualifier;
	if (qualifier != data_types::Qualifier::QUALIFIER_READ_OK) {
		LogError("hardware sensor read error!!!!!!!");
	} else {
			// Update encoder history
		for (int i=0; i<(kWheelSensorHistorySize-1); ++i) {
			for (int j=0; j<4; ++j) {
				mHwEncoder[i][j] = mHwEncoder[i+1][j];
			}
		}
		for (int i=0; i<4; ++i) {
			mHwEncoder[kWheelSensorHistorySize-1][i] = inputData.input.mcuSensors.motorEncoder[i];
		}

		// Update Time
		for (int i=0; i<(kWheelSensorHistorySize-1); ++i) {
			mHwTime[i] = mHwTime[i+1];
		}
		mHwTime[kWheelSensorHistorySize-1] = static_cast<std::uint64_t>(inputData.input.mcuSensors.timestampMsec) * 1000ULL + inputData.input.mcuSensors.timestampUsec;

		// Only start calculate after 5th cycle
		if (cycleCount > 5) {
			updateEncoder();
			updateSpeed();
			updateAcceleration();
			writeOutput();
		}
	}
}

inline void WheelSensor::updateEncoder(void) {
	// Update Encoder
	for (int i=0; i<(kWheelSensorHistorySize-1); ++i) {
		for (int j=0; j<4; ++j) {
			mEncoder[i][j] = mEncoder[i+1][j];
		}
	}
	for (int i=0; i<4; ++i) {
		const int16_t encdiff = uint16_t(mHwEncoder[(kWheelSensorHistorySize-1)][i] - mHwEncoder[(kWheelSensorHistorySize-2)][i]);
		mEncoder[kWheelSensorHistorySize-1][i] += encdiff; //mHwEncoder[(kWheelSensorHistorySize-1)][i] - mHwEncoder[(kWheelSensorHistorySize-2)][i];
	}
}


inline void WheelSensor::updateSpeed(void) {
	// Update Speed
	for (int i=0; i<kWheelSensorHistorySize-2; ++i) {
		for (int j=0; j<4; ++j) {
			mWheelSpeed[i][j] = mWheelSpeed[i+1][j];
		}
	}
	const float timeDiff {static_cast<float>(mHwTime[kWheelSensorHistorySize-1] - mHwTime[kWheelSensorHistorySize-2]) / 1000000.0F};

	for (int i=0; i<4; ++i) {
		const float encoderDiff {static_cast<float>(mEncoder[kWheelSensorHistorySize-1][i] - mEncoder[kWheelSensorHistorySize-2][i])};
		const float rotation {encoderDiff / 2200};
		const float distance {rotation * (3.1415926535F * 0.0254F * 3.0F)};
		mWheelSpeed[kWheelSensorHistorySize-2][i] = distance / timeDiff;	
	}
}

inline void WheelSensor::updateAcceleration(void) {
	for (int i=0; i<kWheelSensorHistorySize-3; ++i) {
		for (int j=0; j<4; ++j) {
			mWheelAcceleration[i][j] = mWheelAcceleration[i+1][j];
		}
	}
	for (int i=0; i<4; ++i) {
		mWheelAcceleration[kWheelSensorHistorySize-3][i] = 
			(mWheelSpeed[kWheelSensorHistorySize-2][i] - mWheelSpeed[kWheelSensorHistorySize-3][i]) / 
			static_cast<float>((mHwTime[kWheelSensorHistorySize-1] - mHwTime[kWheelSensorHistorySize-3])) * 2000000.0F;
	}
}

inline void WheelSensor::writeOutput(void) {
	for (int i=0; i<4; ++i) {
		(mOutputData->wheel)[i].encoder = mEncoder[kWheelSensorHistorySize-1][i];
		(mOutputData->wheel)[i].speed = mWheelSpeed[kWheelSensorHistorySize-2][i];
		(mOutputData->wheel)[i].acceleration = mWheelAcceleration[kWheelSensorHistorySize-3][i];
	}
}

}
}