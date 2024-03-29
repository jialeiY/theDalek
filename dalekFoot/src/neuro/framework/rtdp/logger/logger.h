#ifndef __FRAMEWORK_RTDP_LOGGER_LOGGER_H__
#define __FRAMEWORK_RTDP_LOGGER_LOGGER_H__

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

namespace framework {
namespace rtdp {
namespace logger {
namespace detail {

uint64_t useconds();
void writeLogger(int level, const char *format, ...);
}
}
}
}

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"


#define LogDebug(format, ...) \
	framework::rtdp::logger::detail::writeLogger(0, ANSI_COLOR_BLUE "D[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",framework::rtdp::logger::detail::useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LogInfo(format, ...) \
	framework::rtdp::logger::detail::writeLogger(1, ANSI_COLOR_GREEN "I[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",framework::rtdp::logger::detail::useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LogWarn(format, ...) \
	framework::rtdp::logger::detail::writeLogger(2, ANSI_COLOR_YELLOW "W[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",framework::rtdp::logger::detail::useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LogError(format, ...) \
	framework::rtdp::logger::detail::writeLogger(3, ANSI_COLOR_RED "E[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",framework::rtdp::logger::detail::useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LogFatal(format, ...) \
	framework::rtdp::logger::detail::writeLogger(3, ANSI_COLOR_RED "F[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",framework::rtdp::logger::detail::useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif