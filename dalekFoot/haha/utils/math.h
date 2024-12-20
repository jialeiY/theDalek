#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

#include <cmath>
#include <cstdint>
#include "data/defs/polar_vector2d.h"
#include "data/defs/position2d.h"
#include "data/defs/vector2d.h"
#include "data/gh_protocol.h"

namespace cooboc {
namespace utils {
namespace math {
constexpr float PI {3.141592653589793238462643383279502884197F};
constexpr float FLOAT_EPSILON {1e-6F};

template<typename Tin, typename Tout>
Tout lerp(
  const Tin& x, const Tin& inStart, const Tin& inEnd, const Tout& outStart, const Tout& outEnd) {
    return (x - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

template<typename T>
T clamp(const T& in, const T& minv, const T& maxv) {
    return std::min(std::max(in, minv), maxv);
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

template<typename Ta, typename Tb>
inline Ta to(const Tb& in) {
    return Ta();
}

template<>
inline data::PolarVector2D to<data::PolarVector2D, data::Vector2D>(const data::Vector2D& in) {
    return {std::atan2(in.y, in.x), std::sqrt((in.x * in.x) + (in.y * in.y))};
}

template<>
inline data::Vector2D to<data::Vector2D, data::PolarVector2D>(const data::PolarVector2D& in) {
    return {std::cos(in.orientation) * in.value, std::sin(in.orientation) * in.value};
}

template<typename T>
inline T interpolate(T from, T to, float percent) {
    return from + ((to - from) * percent);
}

template<>
inline data::Vector2D interpolate(data::Vector2D from, data::Vector2D to, float percent) {
    return data::Vector2D {interpolate<float>(from.x, to.x, percent),
                           interpolate<float>(from.y, to.y, percent)};
}

inline data::Vector2D normalize(const data::Vector2D& in) {
    if (equals(in, {0.0F, 0.0F})) {
        return {0.0F, 0.0F};
    } else {
        const float length = in.abs();
        return {in.x / length, in.y / length};
    }
}

inline float clampAngle(float in) {
    in = std::fmod(in, 2.0F * PI);
    if (in > PI) {
        in -= 2.0F * PI;
    }
    if (in < -PI) {
        in += 2.0F * PI;
    }
    return in;
}

std::uint32_t calculateCrc(const uint32_t* payload, const size_t size);

inline std::uint32_t calculateCrc(const comm::HGPacket& spiPacket) {
    return calculateCrc((const uint32_t*)(&spiPacket), ((HG_PACKET_SIZE - 4U) / 4));
}

inline std::uint32_t calculateCrc(const comm::GHPacket& spiPacket) {
    if (reinterpret_cast<std::uintptr_t>(&spiPacket) % 4 == 0) {
        // aligned
        const void* alignedPtr = (const void*)(&spiPacket);
        return calculateCrc(reinterpret_cast<const std::uint32_t*>(alignedPtr),
                            ((GH_PACKET_SIZE - 4U) / 4));
    } else {
        // not aligned
        const cooboc::comm::GHPacket alignedPacket __attribute__((aligned(4))) = spiPacket;
        const void* alignedPtr = (const void*)(&alignedPacket);
        return calculateCrc(reinterpret_cast<const std::uint32_t*>(alignedPtr),
                            ((GH_PACKET_SIZE - 4U) / 4));
    }
}


}    // namespace math
}    // namespace utils
}    // namespace cooboc


#endif
