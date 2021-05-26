#ifndef __MODULE_MEM_MEM_H__
#define __MODULE_MEM_MEM_H__

#include <cstdint>
#include <cstring>

namespace mem {

void memcpy(volatile void *dest, void *src, std::size_t size);
void memcpy(void *dest, volatile void *src, std::size_t size);
void memset(volatile void *dest, std::size_t size, uint8_t value);	
}

#endif


