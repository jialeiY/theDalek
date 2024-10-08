#ifndef __DATA_DEFS_POLAR_VECTOR2D_H__
#define __DATA_DEFS_POLAR_VECTOR2D_H__

#include "data/defs/orientation.h"

namespace cooboc {
namespace data {

struct Vector2D;

struct PolarVector2D {
    Orientation orientation {0.0F};
    float value {0.0F};

    inline PolarVector2D operator*(const float a) const { return {orientation, value * a}; }
};

}    // namespace data
}    // namespace cooboc

#endif
