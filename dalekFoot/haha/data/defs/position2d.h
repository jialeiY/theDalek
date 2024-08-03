#ifndef __DATA_DEFS_POSITION2D_H__
#define __DATA_DEFS_POSITION2D_H__

#include <cmath>

namespace cooboc {
namespace data {

struct Position2D {
    float x {0.0F};
    float y {0.0F};


    inline Position2D operator-(const Position2D &b) const {
        return {x - b.x, y - b.y};
    }
    inline float dot(const Position2D &b) const {
        return (x * b.x) + (y * b.y);
    }
    inline float cross(const Position2D &b) const {
        return (x * b.y) - (y * b.x);
    }
    inline float distance(const data::Position2D &b) const {
        const float diffx = x - b.x;
        const float diffy = y - b.y;
        return std::sqrt((diffx * diffx) + (diffy * diffy));
    }
    inline float abs() const { return std::sqrt((x * x) + (y * y)); }
};


}    // namespace data
}    // namespace cooboc

#endif
