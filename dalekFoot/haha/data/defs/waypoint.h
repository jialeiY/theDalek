#ifndef __DATA_DEFS_WAYPOINT_H__
#define __DATA_DEFS_WAYPOINT_H__

#include "data/defs/pose2d.h"
#include "data/defs/timestamp.h"

namespace cooboc {
namespace data {

struct Waypoint {
    Timestamp timepoint {0U};
    Pose2D pose {};

    float velocityY {0.0F};        // Debug
    float accelerationY {0.0F};    // Deubg
};

}    // namespace data
}    // namespace cooboc

#endif
