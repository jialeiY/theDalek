#ifndef __DATA_DEFSVECTOR2D_H__
#define __DATA_DEFSVECTOR2D_H__

#include <cmath>

namespace cooboc {
namespace data {

struct Vector2D {
    float x {0.0F};
    float y {0.0F};

    inline Vector2D operator-(const Vector2D &b) const { return {x - b.x, y - b.y}; }
    inline float dot(const Vector2D &b) const { return (x * b.x) + (y * b.y); }
    inline float cross(const Vector2D &b) const { return (x * b.y) - (y * b.x); }
    inline float abs() const { return std::sqrt((x * x) + (y * y)); }
    inline float distance(const data::Vector2D &b) const {
        const float diffx = x - b.x;
        const float diffy = y - b.y;
        return std::sqrt((diffx * diffx) + (diffy * diffy));
    }
};

}    // namespace data
}    // namespace cooboc

#endif
