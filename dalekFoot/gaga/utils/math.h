#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__
#include <data/gh_protocol.h>
#include <algorithm>
#include <cstdint>
namespace cooboc {
namespace utils {
namespace math {

constexpr float PI {3.141592653589793238462643383279502884197169399375105820974944F};

template<typename Tin, typename Tout>
Tout lerp(
  const Tin& x, const Tin& inStart, const Tin& inEnd, const Tout& outStart, const Tout& outEnd) {
    return (x - inStart) * (outEnd - outStart) / (inEnd - inStart) + outStart;
}

template<typename T>
T clamp(const T& x, const T& min, const T& max) {
    return std::max(std::min(x, max), min);
}

char* printBits(const std::uint8_t byte, char* buffer);


std::uint32_t calculateCrc(const uint32_t* payload, const size_t size);

inline std::uint32_t calculateCrc(const comm::HGPacket& spiPacket) {
    return calculateCrc((const uint32_t*)(&spiPacket), ((HG_PACKET_SIZE - 4U) / 4));
}

inline std::uint32_t calculateCrc(const comm::GHPacket& spiPacket) {
    return calculateCrc((const uint32_t*)(&spiPacket), ((GH_PACKET_SIZE - 4U) / 4));
}


}    // namespace math
}    // namespace utils
}    // namespace cooboc

#endif
