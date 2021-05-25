#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "hardware/i_hardware.h"
#include "module/data_types/exchange_area.h"
#include "framework/entity_agency.h"
#include "module/data_types/hardware/wheelsensor.h"
#include <string>
namespace hardware {
namespace wheelsensor {

class WheelSensor : public hardware::IHardware {
	public:
		WheelSensor(const std::string &name, framework::EntityAgency &entityAgency);
		virtual ~WheelSensor();
		virtual void updateFromSensor(const data_types::ExchangeArea &inputData);

		WheelStatus getWheelStatus(void) const;

	private:
		WheelStatus mStatus;
};

}
}

#endif

