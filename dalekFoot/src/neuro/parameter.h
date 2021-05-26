#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include <cstdint>


// 1HZ

#define HZ10

#ifdef HZ1
constexpr std::uint64_t kLoopThreadInputTimeout {500000ULL};
constexpr std::uint64_t kLoopThreadInterval {1000000ULL};
#endif

#ifdef HZ10
constexpr std::uint64_t kLoopThreadInputTimeout {50000ULL};
constexpr std::uint64_t kLoopThreadInterval {100000ULL};
#endif

#ifdef HZ100
constexpr std::uint64_t kLoopThreadInputTimeout {8000ULL};
constexpr std::uint64_t kLoopThreadInterval {10000ULL};
#endif

#ifdef HZ1000
constexpr std::uint64_t kLoopThreadInputTimeout {500ULL};
constexpr std::uint64_t kLoopThreadInterval {1000ULL};
#endif


#endif
