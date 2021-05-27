#ifndef __MODULE_DATA_TYPES_ACTION_AREA_H__
#define __MODULE_DATA_TYPES_ACTION_AREA_H__

#include "module/data_types/action/odometry.h"

namespace data_types {


struct ActionData {
	action::odometry::Odometry odometry;
};

}

#endif

