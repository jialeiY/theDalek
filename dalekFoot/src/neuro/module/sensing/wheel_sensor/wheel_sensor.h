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

class WheelSensor : public sensing::ISensor {
	public:
		WheelSensor(const std::string &name, framework::thread::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(std::uint64_t cycleCount, const data_types::HardwareData &inputData);

	private:
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
};

}
}

#endif

