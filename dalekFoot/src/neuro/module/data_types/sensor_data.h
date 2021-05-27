#ifndef __MODULE_DATA_TYPES_SENSOR_AREA_H__
#define __MODULE_DATA_TYPES_SENSOR_AREA_H__

#include "module/data_types/sensing/wheel.h"

namespace data_types {


struct SensorData {
	sensing::Wheel wheel[4];
};

}

#endif

