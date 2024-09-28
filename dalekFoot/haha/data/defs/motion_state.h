#ifndef __DATA_DEFS_MOTION_STATE_H__
#define __DATA_DEFS_MOTION_STATE_H__

#include "data/defs/polar_vector2d.h"

namespace cooboc {
namespace data {
struct MotionState {
    data::PolarVector2D velocity {};        // Ego coordinate m/s
    data::PolarVector2D acceleration {};    // Ego coordinate m/s2
    float angularVelocity {0.0F};           // rad/s
    float angularAcceleration {0.0F};       // rad/s2
};
}    // namespace data
}    // namespace cooboc

#endif
