#include "utils/time.h"
#include <chrono>
#include <cstdint>


namespace cooboc {
namespace utils {
namespace time {

std::uint64_t nanoseconds() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

std::uint64_t milliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

}    // namespace time
}    // namespace utils
}    // namespace cooboc
