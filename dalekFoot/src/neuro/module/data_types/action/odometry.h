#ifndef __MODULE_DATA_TYPES_ACTION_ODOMETRY_H__
#define __MODULE_DATA_TYPES_ACTION_ODOMETRY_H__

#include <stdint.h>



namespace action {
namespace odometry {


struct Odometry {
	// position
	// velocity
	// acceleration
	int16_t value;
	
};

}
}

#endif

