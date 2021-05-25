#ifndef __MODULE_DATA_TYPES_HARDWARE_WHEELSENSOR_H__
#define __MODULE_DATA_TYPES_HARDWARE_WHEELSENSOR_H__


#include <stdint.h>

namespace hardware {
namespace wheelsensor {

struct WheelStatus {
	int16_t encoder[4];
};

}
}


#endif

