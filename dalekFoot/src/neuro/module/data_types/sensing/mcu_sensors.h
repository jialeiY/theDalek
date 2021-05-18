#ifndef __MODULE_DATA_TYPES_SENSING_MCU_SENSORS_H__
#define __MODULE_DATA_TYPES_SENSING_MCU_SENSORS_H__

#include <stdint.h>


namespace sensing {


struct McuSensors {
	uint32_t timestampMsec;
	uint32_t timestampUsec;
	uint16_t motorEncoder[4];
	uint16_t fastAdc[14];
	uint8_t slowAdcIdx;
	uint16_t slowAdc;
	uint8_t userInput;
};



}


#endif

