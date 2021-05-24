#ifndef __MODULE_DATA_TYPES_EXCHANGE_AREA_H__
#define __MODULE_DATA_TYPES_EXCHANGE_AREA_H__

#include "module/data_types/sensing/mcu_sensors.h"

namespace data_types {

namespace detail {
struct Input {
	sensing::McuSensors mcuSensors;
};

}
struct ExchangeArea {
	detail::Input input;
};

}

#endif

