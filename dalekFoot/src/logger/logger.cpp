#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <mutex>

using namespace std;

int Logger::gLogLevel = 0;

Logger::Logger() {
	// size_t fileLength = strlen(filename);
	// mFilename = new char[fileLength + 1];
	// memcpy(mFilename, filename, fileLength+1);
}

void Logger::write(int level, const char *format, ...) {
	if (level < gLogLevel) return ;
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
