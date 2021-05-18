#ifndef __MODULE_MATH_UTILITY_H__
#define __MODULE_MATH_UTILITY_H__

#include <cstdint>
#include <stddef.h>

static uint8_t crc8(const uint8_t * payload, size_t len) {
  uint8_t crc = 0;//0xFF;
  int i;

  while (len--) {
    crc ^= *(payload++);
    for (i=0; i<8; i++)
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
  }

  return crc;
}

inline uint32_t u8array2u32(const uint8_t *v4) {
	return 	uint32_t(v4[3])
	 | uint32_t((v4[2] << 8))
	 | uint32_t((v4[1] << 16))
	 | uint32_t((v4[0] << 24));
}

inline uint16_t u8array2u16(const uint8_t *v2) {
	return (uint16_t(v2[0]) << 8) |	uint16_t(v2[1]);
	 
}



#endif
