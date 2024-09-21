#ifndef __COMMON_DATA_DEFS_WHEEL_ODOMETRY_TOPIC_H__
#define __COMMON_DATA_DEFS_WHEEL_ODOMETRY_TOPIC_H__

#include <cstdint>
#include "common/data_defs/qualifier.h"
#include "common/data_defs/wheel_odometry.h"

namespace cooboc {
namespace data {

struct WheelOdometryTopic {
    // TODO: timestamp
    Qualifier qualifier;
    WheelOdometry wheelOdometry[4];
};


}    // namespace data
}    // namespace cooboc

#endif
