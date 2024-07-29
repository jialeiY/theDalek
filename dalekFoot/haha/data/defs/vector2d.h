#ifndef __DATA_DEFS_VECTOR2D_H__
#define __DATA_DEFS_VECTOR2D_H__

#include "data/defs/orientation.h"

namespace cooboc {
namespace data {

struct Vector2D {
    Orientation orientation {0.0F};
    float value {0.0F};
};

}    // namespace data
}    // namespace cooboc

#endif
