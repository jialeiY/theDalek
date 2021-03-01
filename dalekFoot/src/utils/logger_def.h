#ifndef __LOGGER_DEF_H__
#define __LOGGER_DEF_H__


#include <stdio.h>
#include "utils/utils.h"

class Logger {
	public:
		Logger();
		void write(int level, const char *format, ...);
		static void setLogLevel(int ll) {gLogLevel = ll;}
	private:
		char *mFilename;
		static int gLogLevel;
};


#endif