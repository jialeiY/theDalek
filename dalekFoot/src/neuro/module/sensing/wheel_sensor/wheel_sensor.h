#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "module/sensing/i_sensor.h"
#include "module/data_types/hardware_data.h"
#include "framework/entity_agency.h"
#include "module/data_types/sensing/wheel_sensor_data.h"
#include "parameter.h"
#include <string>
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

class WheelSensor : public sensing::ISensor {
	public:
		WheelSensor(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(std::uint64_t cycleCount, const data_types::HardwareData &inputData);

	private:
		void warmupWork(const data_types::HardwareData &inputData);

		std::int16_t mHwEncoder[kWheelSensorHistorySize][4];
		sensing::WheelSensorData mWheelData[4];
};

}
}

#endif

