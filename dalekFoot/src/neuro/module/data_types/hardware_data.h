#ifndef __MODULE_DATA_TYPES_EXCHANGE_AREA_H__
#define __MODULE_DATA_TYPES_EXCHANGE_AREA_H__

#include "module/data_types/hardware/mcu_sensors.h"
#include <cstdint>
namespace data_types {

namespace detail {
struct Input {
	hardware::McuSensors mcuSensors;
};

struct Output {
	// for debug
	std::uint8_t value;
};

}
struct HardwareData {
	std::uint64_t cycleStartTime;
	detail::Input input;
	detail::Output output;
};

}

#endif

