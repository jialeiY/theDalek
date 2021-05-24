#include "module/mem/mem.h"
#include <stdio.h>

namespace mem {



void memcpy(volatile void *dest, void *src, size_t size) {
	volatile uint8_t *dptr = static_cast<volatile uint8_t *>(dest);
	uint8_t *sptr = static_cast<uint8_t *>(src);
	while (size) {
		*dptr = *sptr;
		dptr++;
		sptr++;
		size --;
	}
}

void memcpy(void *dest, volatile void *src, size_t size) {
	uint8_t *dptr = static_cast<uint8_t *>(dest);
	volatile uint8_t *sptr = static_cast<volatile uint8_t *>(src);
	while (size) {
		*dptr = *sptr;
		dptr++;
		sptr++;
		size --;
	}
}

}


