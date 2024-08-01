#ifndef __DATA_DEFS_POSE_H__
#define __DATA_DEFS_POSE_H__

#include "data/defs/orientation.h"
#include "data/defs/position2d.h"

namespace cooboc {
namespace data {

struct Pose2D {
    Position2D position {0.0F, 0.0F};
    Orientation orientation {0.0F};
};

}    // namespace data
}    // namespace cooboc

#endif
