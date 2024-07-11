#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__
#include <algorithm>
#include <cstdint>

namespace cooboc {
namespace math {

template<typename Tin, typename Tout>
Tout lerp(const Tin& x,
          const Tin& inStart,
          const Tin& inEnd,
          const Tout& outStart,
          const Tout& outEnd) {
    return (x - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

template<typename T>
T clamp(const T& x, const T& min, const T& max) {
    return std::max(std::min(x, max), min);
}

char* printBits(const std::uint8_t byte, char* buffer);


}    // namespace math
}    // namespace cooboc

#endif
