#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__


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


}    // namespace math
}    // namespace cooboc

#endif
