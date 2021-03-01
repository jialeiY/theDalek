#ifndef __LOGGER_H__
#define __LOGGER_H__


#include "logger_def.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"


#define critical(format, ...) \
	fprintf(stdout, ANSI_COLOR_RED "D[%s:%d] " ANSI_COLOR_RESET format "\n", __FILE__, __LINE__, ##__VA_ARGS__)




static Logger logger;
#define Ldebug(format, ...) \
	logger.write(0, ANSI_COLOR_BLUE "D[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Linfo(format, ...) \
	logger.write(1, ANSI_COLOR_GREEN "I[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Lwarn(format, ...) \
	logger.write(2, ANSI_COLOR_YELLOW "W[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Lerror(format, ...) \
	logger.write(3, ANSI_COLOR_RED "E[%llu %s:%s():%d] " ANSI_COLOR_RESET format "\n",useconds(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)




#endif



