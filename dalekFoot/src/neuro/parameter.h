#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <cstdint>


// 1HZ

#define HZ10

#ifdef HZ1
constexpr std::uint64_t kLoopThreadInputTimeout {500000ULL};
constexpr std::uint64_t kLoopThreadInterval {1000000ULL};
constexpr std::size_t kFailCountToFailsafe {3U};
#endif

#ifdef HZ10
constexpr std::uint64_t kLoopThreadInputTimeout {80000ULL};
constexpr std::uint64_t kLoopThreadInterval {100000ULL};
constexpr std::size_t kFailCountToFailsafe {5U};
#endif

#ifdef HZ100
constexpr std::uint64_t kLoopThreadInputTimeout {8000ULL};
constexpr std::uint64_t kLoopThreadInterval {10000ULL};
constexpr std::size_t kFailCountToFailsafe {30U};
#endif

#ifdef HZ1000
constexpr std::uint64_t kLoopThreadInputTimeout {500ULL};
constexpr std::uint64_t kLoopThreadInterval {1000ULL};
constexpr std::size_t kFailCountToFailsafe {50U};
#endif

constexpr std::size_t kWheelSensorHistorySize {3U};

constexpr std::size_t kPersistentWriterBufferSize {128U};

#endif
