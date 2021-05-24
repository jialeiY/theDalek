#ifndef __MODULE_DATA_TYPES_EXCHANGE_AREA_H__
#define __MODULE_DATA_TYPES_EXCHANGE_AREA_H__

#include "module/data_types/sensing/mcu_sensors.h"

namespace data_types {

struct ExchangeArea {
	struct sensors {
		sensing::McuSensors mcuSensors;
	};
};

}

#endif

