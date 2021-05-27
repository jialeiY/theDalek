#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "module/sensing/i_sensor.h"
#include "module/data_types/hardware_data.h"
#include "framework/entity_agency.h"
#include "module/data_types/sensing/wheel.h"
#include <string>
#include <cstdint>

namespace sensing {
namespace wheel_sensor {

class WheelSensor : public sensing::ISensor {
	public:
		WheelSensor(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(const data_types::HardwareData &inputData);

	private:
		
		
};

}
}

#endif

