#ifndef __MODULE_DATA_TYPES_EXCHANGE_AREA_H__
#define __MODULE_DATA_TYPES_EXCHANGE_AREA_H__

#include "module/data_types/hardware/mcu_sensors.h"
#include <cstdint>
namespace data_types {

namespace detail {
struct Input {
	std::uint64_t cycleStartTime;
	hardware::McuSensors mcuSensors;
};

struct Output {
	// for debug
	std::uint64_t cycleStartTime;
	std::uint8_t value;
};

}
struct HardwareData {
	detail::Input input;
	detail::Output output;
};

}

#endif

