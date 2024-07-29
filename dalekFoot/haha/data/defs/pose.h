#ifndef __DATA_DEFS_POSE_H__
#define __DATA_DEFS_POSE_H__

#include "data/defs/orientation.h"
#include "data/defs/position2d.h"

namespace cooboc {
namespace data {

struct Pose {
    Position2D position;
    Orientation orientation;
};

}    // namespace data
}    // namespace cooboc

#endif
