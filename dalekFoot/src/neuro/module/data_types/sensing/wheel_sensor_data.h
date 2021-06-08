#ifndef __MODULE_DATA_TYPES_SENSING_WHEEL_SENSOR_DATA_H__
#define __MODULE_DATA_TYPES_SENSING_WHEEL_SENSOR_DATA_H__

#include "module/data_types/qualifer.h"
#include <cstdint>

namespace sensing {

namespace detail {

struct WheelData {
	std::int64_t encoder;
	float speed;
	float acceleration;
};

}

struct WheelSensorData {
	data_types::Qualifier qualifier;
	std::uint64_t measurementTime;
	detail::WheelData wheel[4];
};


}


#endif

