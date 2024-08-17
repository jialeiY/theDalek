#include "data/defs/vector2d.h"
#include "data/defs/polar_vector2d.h"


namespace cooboc {
namespace data {
Vector2D Vector2D::operator+(const PolarVector2D &b) const {
    return Vector2D {x + (std::cos(b.orientation) * b.value),
                     y + (std::sin(b.orientation) * b.value)};
}

Vector2D Vector2D::operator-(const PolarVector2D &b) const {
    return Vector2D {x - (std::cos(b.orientation) * b.value),
                     y - (std::sin(b.orientation) * b.value)};
}

}    // namespace data
}    // namespace cooboc