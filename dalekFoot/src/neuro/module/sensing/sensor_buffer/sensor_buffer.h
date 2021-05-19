#ifndef __MODULE_SENSING_SENSOR_BUFFER_SENSOR_BUFFER_H__
#define __MODULE_SENSING_SENSOR_BUFFER_SENSOR_BUFFER_H__

#include "module/data_types/sensing/mcu_sensors.h"

namespace sensing {

class SensorBuffer {
	public:
		void update(const McuSensors &mcuSensors);
		void printStatus(void) const;



		

};

}

#endif

