#ifndef __DATA_DEFS_ODOMETRY_H__
#define __DATA_DEFS_ODOMETRY_H__

#include "data/defs/pose.h"

namespace cooboc {
namespace data {

struct Odometry {
    // World coordinate
    Pose pose;
};

}    // namespace data
}    // namespace cooboc

#endif
