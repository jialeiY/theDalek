#ifndef __INTENTS_COMMON_DATA_DEFS_WHEEL_ODOMETRY_TOPIC_H__
#define __INTENTS_COMMON_DATA_DEFS_WHEEL_ODOMETRY_TOPIC_H__

#include <cstdint>
#include "intents/common/data_defs/qualifier.h"

namespace cooboc {
namespace data {

struct WheelSpeed {
    Qualifier qualifier;
    float speed;    // m / s
};

struct WheelOdometryTopic {
    // TODO: timestamp
    Qualifier qualifier;

    // // TODO: not implemented yet
    // float x;    // m
    // float y;    // m
    // float r;    // m

    WheelSpeed wheelSpeed[4];
};


}    // namespace data
}    // namespace cooboc

#endif
