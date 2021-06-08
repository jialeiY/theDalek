#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "module/data_types/hardware_data.h"
#include "framework/rtdp/logger/logger.h"
#include "parameter.h"
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

namespace detail {
inline float calculateSpeed(std::int16_t encDiff, std::uint64_t timeLapse) {
	const float encDist = static_cast<float>(encDiff);
	const float rotation = encDist / 2200.0F;
	const float dist = rotation * (3.1415926535F * 0.0254F * 3.0F);
	const float speed = dist / timeLapse / 1000000.0F;
	return speed;
}
}


WheelSensor::WheelSensor(const std::string &name, framework::thread::EntityAgency &entityAgency) :
	ISensor(name, entityAgency),
	mFailCount {0U},
	mIsFailsafe {false},
	mGoodDataCount {0U} {
	for (int i=0; i<4; ++i) {
		mEncoder[i] = 0U;
	}
}

WheelSensor::~WheelSensor() {
	
}


void WheelSensor::updateFromSensor(const std::uint64_t cycleCount, const data_types::HardwareData &hardwareData) {
	if (mIsFailsafe) {
		LogError("WheelSensor in failsafe, exited");
		mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_ERROR_FAILSAFE;
		return ;
	}

	if (hardwareData.input.mcuSensors.qualifier != data_types::Qualifier::QUALIFIER_READ_OK) {
		handleUnqualifiedData(cycleCount, hardwareData);
	} else {
		handleNormalData(cycleCount, hardwareData);
	}
	
	
	/*
	const data_types::Qualifier & qualifier = hardwareData.input.mcuSensors.qualifier;
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
			mHwEncoder[kWheelSensorHistorySize-1][i] = hardwareData.input.mcuSensors.motorEncoder[i];
		}

		// Update Time
		for (int i=0; i<(kWheelSensorHistorySize-1); ++i) {
			mHwTime[i] = mHwTime[i+1];
		}
		mHwTime[kWheelSensorHistorySize-1] = static_cast<std::uint64_t>(hardwareData.input.mcuSensors.timestampMsec) * 1000ULL + hardwareData.input.mcuSensors.timestampUsec;

		// Only start calculate after 5th cycle
		if (cycleCount > 5) {
			updateEncoder();
			updateSpeed();
			updateAcceleration();
			writeOutput();
		}
	}
	*/
}

inline void WheelSensor::handleUnqualifiedData(const std::uint64_t cycleCount, const data_types::HardwareData &inputData) {
	LogDebug("unqualified data found");
	mFailCount ++;
	if (mFailCount < kFailCountToFailsafe) {
		mOutputData->wheelSensor.qualifier = inputData.input.mcuSensors.qualifier;
	} else {
		LogFatal("Wheel Sensor entering FAILSAFE");
		mIsFailsafe = true;
		mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_ERROR_FAILSAFE;
	}
}

inline void WheelSensor::handleNormalData(const std::uint64_t cycleCount, const data_types::HardwareData &inputData) {
	mFailCount = 0;
	mGoodDataCount ++;
	// Validate time
	const std::uint64_t mcuMeasureTime = static_cast<std::uint64_t>(inputData.input.mcuSensors.timestampMsec) * 1000ULL + inputData.input.mcuSensors.timestampUsec;
	const std::uint64_t neuroMeasureTime = inputData.input.cycleStartTime;
	const std::int64_t measureTimeOffset = mcuMeasureTime - neuroMeasureTime;
	

	// Update historical data
	for (int i=0; i<2; ++i) {
		for (int j=0; j<4; ++j) {
			mHwEncoder[i][j] = mHwEncoder[i+1][j];
		}
		mMcuMeasurementTime[i] = mMcuMeasurementTime[i+1];
		mNeuroMeasurementTime[i] = mNeuroMeasurementTime[i+1];
	}
	for (int i=0; i<4; ++i) {
		mHwEncoder[2][i] = inputData.input.mcuSensors.motorEncoder[i];
	}
	mMcuMeasurementTime[2]	= mcuMeasureTime;
	mNeuroMeasurementTime[2] = neuroMeasureTime;

	if (mGoodDataCount >= 2) {
		const std::uint64_t timeLapse = mNeuroMeasurementTime[2] - mNeuroMeasurementTime[1];
		float currentSpeed[4];
		std::int16_t encoderDiff[4];
		for (int i=0; i<4; ++i) {
			encoderDiff[i] = mHwEncoder[2][i] - mHwEncoder[1][i];
			currentSpeed[i] = detail::calculateSpeed(encoderDiff[i], timeLapse);
		}

		if (mGoodDataCount >= 3) {
			mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_READ_OK;
			uint64_t timeDiff = mMcuMeasurementTime[2] - mMcuMeasurementTime[0];

			// fill the data

			for (int i=0; i<4; ++i) {
				mEncoder[i] += encoderDiff[i];
				const float speedDiff = currentSpeed[i] - mSpeed[i];
				mOutputData->wheelSensor.wheel[i].encoder = mEncoder[i];
				mOutputData->wheelSensor.wheel[i].speed = currentSpeed[i];
				mOutputData->wheelSensor.wheel[i].acceleration = speedDiff / timeDiff * 2.0F;
			}
			
			
		} else {
			mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_ERROR_NOT_READY;
		}


		for (int i=0; i<4; ++i) {
			mSpeed[i] = currentSpeed[i];
		}
	}	
}

/*
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
		(mOutputData->wheelSensor)[i].encoder = mEncoder[kWheelSensorHistorySize-1][i];
		(mOutputData->wheelSensor)[i].speed = mWheelSpeed[kWheelSensorHistorySize-2][i];
		(mOutputData->wheelSensor)[i].acceleration = mWheelAcceleration[kWheelSensorHistorySize-3][i];
	}
}

*/

}
}