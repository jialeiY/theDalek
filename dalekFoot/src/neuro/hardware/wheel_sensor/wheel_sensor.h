#ifndef __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__
#define __HARDWARE_WHEEL_SENSOR_WHEEL_SENSOR_H__

#include "hardware/i_hardware.h"

namespace hardware {
namespace wheelsensor {

class WheelSensor : public hardware::IHardware{
	public:
		WheelSensor();
		virtual ~WheelSensor();
};

}
}

#endif

