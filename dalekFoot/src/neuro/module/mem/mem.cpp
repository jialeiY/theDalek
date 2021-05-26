#include "module/mem/mem.h"
#include <stdio.h>

namespace mem {



void memcpy(volatile void *dest, void *src, std::size_t size) {
	volatile uint8_t *dptr = static_cast<volatile uint8_t *>(dest);
	uint8_t *sptr = static_cast<uint8_t *>(src);
	while (size) {
		*dptr = *sptr;
		dptr++;
		sptr++;
		size --;
	}
}

void memcpy(void *dest, volatile void *src, std::size_t size) {
	uint8_t *dptr = static_cast<uint8_t *>(dest);
	volatile uint8_t *sptr = static_cast<volatile uint8_t *>(src);
	while (size) {
		*dptr = *sptr;
		dptr++;
		sptr++;
		size --;
	}
}

void memset(volatile void *dest, std::size_t size, uint8_t value) {
	volatile uint8_t *dptr = static_cast<volatile uint8_t *>(dest);
	for (std::size_t i=0; i<size; ++i) {
		dptr[i] = value;
	}
}

}


