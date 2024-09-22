#include "utils/math.h"
#include <data/gh_protocol.h>
#include <cstdint>

namespace cooboc {
namespace utils {
namespace math {


char *printBits(const std::uint8_t byte, char *buffer) {
    for (std::size_t i {0U}; i < 8U; ++i) {
        buffer[i] = (byte & (0x01 << (7U - i))) == 0 ? '0' : '1';
    }
    buffer[8U] = '\0';
    return buffer;
}


std::uint32_t calculateCrc(const uint32_t *payload, const size_t size) {
    constexpr uint32_t kInitCrc {0x777086AA};
    constexpr uint32_t kPoly {0x2783DA2B};

    uint32_t crc = kInitCrc;
    for (std::size_t i {0U}; i < size; ++i) {
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