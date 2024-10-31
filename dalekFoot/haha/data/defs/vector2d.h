#ifndef __DATA_DEFSVECTOR2D_H__
#define __DATA_DEFSVECTOR2D_H__

#include <cmath>
#include "data/defs/polar_vector2d.h"

namespace cooboc {
namespace data {


struct Vector2D {
    float x {0.0F};
    float y {0.0F};

    inline Vector2D operator-(const Vector2D &b) const {
        return {x - b.x, y - b.y};
    }

    inline Vector2D operator+(const Vector2D &b) const {
        return {x + b.x, y + b.y};
    }


    inline Vector2D operator+(const PolarVector2D &b) const {
        return Vector2D {x + (std::cos(b.orientation) * b.value),
                         y + (std::sin(b.orientation) * b.value)};
    }

    inline Vector2D operator-(const PolarVector2D &b) const {
        return Vector2D {x - (std::cos(b.orientation) * b.value),
                         y - (std::sin(b.orientation) * b.value)};
    }


    inline Vector2D operator*(const float a) const {
        return {x * a, y * a};
    }

    inline Vector2D operator/(const float a) const {
        return {x / a, y / a};
    }

    inline float dot(const Vector2D &b) const {
        return (x * b.x) + (y * b.y);
    }

    inline float cross(const Vector2D &b) const {
        return (x * b.y) - (y * b.x);
    }

    inline float abs() const {
        return std::sqrt((x * x) + (y * y));
    }

    inline float distance(const data::Vector2D &b) const {
        const float diffX = x - b.x;
        const float diffY = y - b.y;
        return std::sqrt((diffX * diffX) + (diffY * diffY));
    }
};

}    // namespace data
}    // namespace cooboc

#endif
