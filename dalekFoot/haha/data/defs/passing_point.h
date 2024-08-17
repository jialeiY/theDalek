#ifndef __DATA_DEFS_PASSING_POINT_H__
#define __DATA_DEFS_PASSING_POINT_H__

#include "data/defs/position2d.h"

namespace cooboc {
namespace data {
// WIP
struct PassingPoint {
    data::Position2D position;    // in world
    // float speed;
    //  orientation or curvature to the last segment
};
}    // namespace data
}    // namespace cooboc

#endif
