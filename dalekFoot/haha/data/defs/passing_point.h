#ifndef __DATA_DEFS_PASSING_POINT_H__
#define __DATA_DEFS_PASSING_POINT_H__

#include "data/defs/orientation.h"
#include "data/defs/position2d.h"

namespace cooboc {
namespace data {

struct PassingPoint {
    Position2D position;        // in the world
    Orientation orientation;    // in the World
};
}    // namespace data
}    // namespace cooboc

#endif
