#ifndef __MODULE_DATA_TYPES_SENSING_WHEEL_SENSOR_DATA_H__
#define __MODULE_DATA_TYPES_SENSING_WHEEL_SENSOR_DATA_H__


#include <cstdint>

namespace sensing {

struct WheelSensorData {
	std::uint64_t encoder;
	float speed;
	float acceleration;
};


}


#endif

