#ifndef __MODULE_DATA_TYPES_HARDWARE_MCU_SENSORS_H__
#define __MODULE_DATA_TYPES_HARDWARE_MCU_SENSORS_H__

#include <cstdint>


namespace hardware {


struct McuSensors {
	std::uint32_t timestampMsec;
	std::uint32_t timestampUsec;
	std::int16_t motorEncoder[4];
	std::uint16_t fastAdc[14];
	std::uint8_t slowAdcIdx;
	std::uint16_t slowAdc;
	std::uint8_t userInput;
};



}


#endif

