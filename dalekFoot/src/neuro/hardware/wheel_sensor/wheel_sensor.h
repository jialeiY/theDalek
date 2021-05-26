#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "hardware/i_hardware.h"
#include "module/data_types/exchange_area.h"
#include "framework/entity_agency.h"
#include "module/data_types/sensing/wheel_status.h"
#include <string>
namespace hardware {
namespace wheel_sensor {

class WheelSensor : public hardware::IHardware {
	public:
		WheelSensor(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(const data_types::ExchangeArea &inputData);

		sensing::WheelStatus getWheelStatus(void) const;

	private:
		sensing::WheelStatus mStatus;
};

}
}

#endif

