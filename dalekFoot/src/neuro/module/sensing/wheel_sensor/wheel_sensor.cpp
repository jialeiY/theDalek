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
	const float speed = dist / timeLapse * 1000000.0F;
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
	LogDebug("cyc: %llu, enc: %d", cycleCount, hardwareData.input.mcuSensors.motorEncoder[3]);
	if (kIsFailsafeEnabled && mIsFailsafe) {
		LogError("WheelSensor in failsafe, exited");
		mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_ERROR_FAILSAFE;
		return ;
	}

	if (hardwareData.input.mcuSensors.qualifier != data_types::Qualifier::QUALIFIER_READ_OK) {
		handleUnqualifiedData(cycleCount, hardwareData);
	} else {
		handleNormalData(cycleCount, hardwareData);
	}
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

int maxFailCount = 0;
inline void WheelSensor::handleNormalData(const std::uint64_t cycleCount, const data_types::HardwareData &inputData) {
	if (mFailCount > maxFailCount) {
		LogDebug("max fail count occur: %d", maxFailCount);
		maxFailCount = mFailCount;
	}
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
			LogDebug("enc: %ld, speed: %f", 
				mOutputData->wheelSensor.wheel[3].encoder,
				mOutputData->wheelSensor.wheel[3].speed);
			
			
		} else {
			mOutputData->wheelSensor.qualifier = data_types::Qualifier::QUALIFIER_ERROR_NOT_READY;
		}


		for (int i=0; i<4; ++i) {
			mSpeed[i] = currentSpeed[i];
		}
	}	
}

}
}