#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "module/sensing/i_sensor.h"
#include "framework/thread/entity_agency.h"
#include "module/data_types/hardware_data.h"
#include "module/data_types/sensing/wheel_sensor_data.h"
#include "module/data_types/sensor_data.h"
#include "parameter.h"
#include <string>
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

namespace detail {

float calculateSpeed(std::int16_t currentEnc, std::int16_t lastEnc, std::uint64_t timeLapse);

}

class WheelSensor : public sensing::ISensor {
	public:
		WheelSensor(const std::string &name, framework::thread::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(const std::uint64_t cycleCount, const data_types::HardwareData &inputData);

	private:
		std::size_t mFailCount;
		bool mIsFailsafe;

		std::int16_t mHwEncoder[3][4];
		std::int64_t mEncoder[4];
		std::uint64_t mNeuroMeasurementTime[3];
		std::uint64_t mMcuMeasurementTime[3];
		std::uint64_t mGoodDataCount;
		
		float mSpeed[4];



		void handleUnqualifiedData(const std::uint64_t cycleCount, const data_types::HardwareData &inputData);
		void handleNormalData(const std::uint64_t cycleCount, const data_types::HardwareData &inputData);
		/*

		std::int16_t mHwEncoder[kWheelSensorHistorySize][4];
		std::uint64_t mHwTime[kWheelSensorHistorySize];
		sensing::WheelSensorData mWheelData[4];
		
		std::int32_t mEncoder[kWheelSensorHistorySize][4];
		float mWheelSpeed[kWheelSensorHistorySize-1][4];
		float mWheelAcceleration[kWheelSensorHistorySize-2][4];
		
		void updateEncoder(void);
		void updateSpeed(void);
		void updateAcceleration(void);
		void writeOutput(void);
		*/


};

}
}

#endif

