#ifndef __DRIVER_SERIAL_H__
#define __DRIVER_SERIAL_H__

#include "inc.h"
#include <stdint.h>

constexpr uint32_t SERIAL_RING_BUFFER_SIZE {128};
// #define SERIAL_RING_BUFFER_SIZE 128

class Serial {
	friend void serial1FriendIrq(void);
	public:
		void init(void);
		void println(const char *str);
		void printf(const char *fmt, ...);
		void write(const uint8_t data);
	private:
		uint8_t mRingBuffer[SERIAL_RING_BUFFER_SIZE];
		uint8_t *mPushPtr;
		uint8_t *mPopPtr;
		uint8_t *M_BUFFER_END;
		bool isTransmitting;

		bool isRingBufferFull() const;
		bool isRingBufferEmpty() const;
		void irq();
};

extern Serial Serial1;


#endif

