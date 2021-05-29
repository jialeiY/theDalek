#ifndef __MODULE_DATA_TYPES_ACTION_ODOMETRY_DATA_H__
#define __MODULE_DATA_TYPES_ACTION_ODOMETRY_DATA_H__

#include <stdint.h>



namespace action {
namespace odometry {


struct OdometryData {
	// position
	// velocity
	// acceleration
	int16_t value;
	
};

}
}

#endif

