#ifndef __MODULE_MEM_MEM_H__
#define __MODULE_MEM_MEM_H__

#include <stdint.h>
#include <cstring>

namespace mem {

void memcpy(volatile void *dest, void *src, size_t size);
void memcpy(void *dest, volatile void *src, size_t size);
	
}

#endif


