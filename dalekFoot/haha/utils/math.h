#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

#include <cmath>
#include <cstdint>
#include "data/defs/position2d.h"

namespace cooboc {
namespace utils {
namespace math {
constexpr float PI {3.141592653589793238462643383279502884197F};
constexpr float FLOAT_EPSILON {1e-6F};


template<typename Tin, typename Tout>
Tout lerp(const Tin& x, const Tin& inStart, const Tin& inEnd, const Tout& outStart, const Tout& outEnd) {
    return (x - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

template<typename T>
inline bool equals(const T& a, const T& b) {
    return a == b;
}

template<>
inline bool equals<float>(const float& a, const float& b) {
    return std::fabs(a - b) < FLOAT_EPSILON;
}

template<>
inline bool equals<data::Position2D>(const data::Position2D& a, const data::Position2D& b) {
    return equals(a.x, b.x) && equals(a.y, b.y);
}


}    // namespace math
}    // namespace utils
}    // namespace cooboc


#endif
