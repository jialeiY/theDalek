#include "math/utils.h"
#include <cstdint>

namespace cooboc {
namespace math {


char *printBits(const std::uint8_t byte, char *buffer) {
    for (std::size_t i {0U}; i < 8U; ++i) {
        buffer[i] = (byte & (0x01 << (7U - i))) == 0 ? '0' : '1';
    }
    buffer[8U] = '\0';
    return buffer;
}

}    // namespace math
}    // namespace cooboc