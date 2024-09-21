#ifndef __COMMON_DATA_DEFS_WHEEL_ODOMETRY_H__
#define __COMMON_DATA_DEFS_WHEEL_ODOMETRY_H__

#include <cstdint>
#include "common/data_defs/qualifier.h"

namespace cooboc {
namespace data {

struct WheelOdometry {
    Qualifier qualifier {Qualifier::BAD};
    std::int32_t odometry {0};    // encoder unit


    WheelOdometry operator+(const WheelOdometry &b) {
        WheelOdometry ret {Qualifier::BAD, 0};
        if ((qualifier == Qualifier::BAD) || (b.qualifier == Qualifier::BAD)) {
            return ret;
        }

        if ((qualifier == Qualifier::DEGRADED) || (b.qualifier == Qualifier::DEGRADED)) {
            ret.qualifier = Qualifier::DEGRADED;
            ret.odometry  = odometry + b.odometry;
            return ret;
        }

        ret.qualifier = Qualifier::GOOD;
        ret.odometry  = odometry + b.odometry;
        return ret;
    }
};

}    // namespace data
}    // namespace cooboc

#endif
