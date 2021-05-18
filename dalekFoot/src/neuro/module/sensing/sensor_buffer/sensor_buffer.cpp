
#include "module/sensing/sensor_buffer/sensor_buffer.h"
#include "module/data_types/sensing/mcu_sensors.h"
#include <stdio.h>

namespace sensing {

void SensorBuffer::update(const McuSensors &mcuSensors) {
	printf("time from mcu: %u\r\n", mcuSensors.timestampMsec);
	
	for (int i=0; i<14; ++i) {
		printf("%u ", mcuSensors.fastAdc[i]);
	}
	printf("\r\n");
}

}