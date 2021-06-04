
#include "framework/rtdp/logger/logger.h"

#include <stdint.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace framework {
namespace rtdp {
namespace logger {
namespace detail {

int gLogLevel = 0;

uint64_t useconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec + (uint64_t)(tv.tv_sec * 1000000ULL);
}



void writeLogger(int level, const char *format, ...) {
	if (level < gLogLevel) return ;
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

}
}
}
}

