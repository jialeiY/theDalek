#ifndef __FRAMEWORK_EVENT_TYPE_H__
#define __FRAMEWORK_EVENT_TYPE_H__


#include <cstdint>


enum EventType : uint64_t {
	GLOBAL_CYCLE_START,
	IO_FINISHED,
	CONTROL_FINISHED,

	EMPTY = 0xFFFFFFFFFFFFFFFF
};


#endif

