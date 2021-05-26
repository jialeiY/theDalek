#ifndef __MODULE_DATA_TYPES_EXCHANGE_AREA_H__
#define __MODULE_DATA_TYPES_EXCHANGE_AREA_H__

#include "module/data_types/hardware/mcu_sensors.h"

namespace data_types {

namespace detail {
struct Input {
	hardware::McuSensors mcuSensors;
};

struct Output {
	
};

}
struct ExchangeArea {
	detail::Input input;
	detail::Output output;
};

}

#endif

