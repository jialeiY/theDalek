#ifndef __MODULE_DATA_TYPES_SENSOR_AREA_H__
#define __MODULE_DATA_TYPES_SENSOR_AREA_H__

#include "module/data_types/sensing/wheel_sensor_data.h"

namespace data_types {


struct SensorData {
	sensing::WheelSensorData wheelSensor;
};

}

#endif

