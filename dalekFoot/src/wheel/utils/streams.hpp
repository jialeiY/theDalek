#ifndef __UTILS_STREAMS_H__
#define __UTILS_STREAMS_H__

#include <stdint.h>
#include <stdarg.h>

namespace cooboc {

uint32_t sprintf(char *dest, const char * const fmt, ...);
uint32_t vsprintf(char *dest, const char *fmt, va_list ap);
}

#endif

