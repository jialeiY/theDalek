#ifndef __MODULE_DATA_TYPES_SENSING_WHEEL_STATUS_H__
#define __MODULE_DATA_TYPES_SENSING_WHEEL_STATUS_H__


#include <cstdint>

namespace sensing {

struct Wheel {
	std::int16_t encoder[4];
};


}


#endif

