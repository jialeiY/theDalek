#ifndef __MODULE_DATA_TYPES_SENSOR_AREA_H__
#define __MODULE_DATA_TYPES_SENSOR_AREA_H__

#include "module/data_types/action/odometry.h"

namespace data_types {


struct SensorData {
	action::odometry::Odometry odometry;
};

}

#endif

