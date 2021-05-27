
#include "module/time/time.h"
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdint>

namespace times {

#ifndef NULL
#define NULL 0
#endif

std::uint64_t useconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<uint64_t>(tv.tv_usec) + static_cast<uint64_t>(tv.tv_sec) * 1000000ULL;
}


}