#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

#include <cstdint>


namespace cooboc {
namespace utils {
namespace math {
constexpr float PI {3.141592653589793238462643383279502884197F};

template<typename Tin, typename Tout>
Tout lerp(const Tin& x,
          const Tin& inStart,
          const Tin& inEnd,
          const Tout& outStart,
          const Tout& outEnd) {
    return (x - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

}    // namespace math
}    // namespace utils
}    // namespace cooboc


#endif
