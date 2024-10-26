#include "utils/math.h"

namespace cooboc {
namespace utils {
namespace math {
std::uint32_t calculateCrc(const uint32_t *payload, const size_t numberOfWords) {
    constexpr uint32_t kInitCrc {0x777086AA};
    constexpr uint32_t kPoly {0x2783DA2B};

    uint32_t crc = kInitCrc;
    for (std::size_t i {0U}; i < numberOfWords; ++i) {
        if ((crc & 0x80000000) != 0) {
            crc <<= 1;
            crc ^= kPoly;
        } else {
            crc <<= 1;
        }
        crc ^= payload[i];
    }
    return crc;
}
}    // namespace math
}    // namespace utils
}    // namespace cooboc
