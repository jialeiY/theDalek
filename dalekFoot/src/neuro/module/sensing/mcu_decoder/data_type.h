#ifndef __MODULE_SENSING_MCU_DECODER_DATA_TYPE_H__
#define __MODULE_SENSING_MCU_DECODER_DATA_TYPE_H__

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

