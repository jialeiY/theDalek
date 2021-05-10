#ifndef __FRAMEWORK_EVENT_TYPE_H__
#define __FRAMEWORK_EVENT_TYPE_H__


#include <cstdint>


enum EventType : uint64_t {
	GLOBAL_CYCLE_START,
	IO_MCU_RESPONSE_TIMEOUT,

	EMPTY = 0xFFFFFFFFFFFFFFFF
};


#endif

