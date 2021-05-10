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



#endif
