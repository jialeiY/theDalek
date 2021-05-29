#ifndef __MODULE_DATA_TYPES_ACTION_AREA_H__
#define __MODULE_DATA_TYPES_ACTION_AREA_H__

#include "module/data_types/action/odometry_data.h"
#include "module/data_types/action/power_data.h"

namespace data_types {


struct ActionData {
	action::odometry::OdometryData odometry;
	action::power::PowerData power;
};

}

#endif

