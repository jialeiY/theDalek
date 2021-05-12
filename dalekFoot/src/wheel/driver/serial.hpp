#ifndef __DRIVER_SERIAL_H__
#define __DRIVER_SERIAL_H__

#include "inc.h"
#include <stdint.h>
#include "modules/decoder/decoder.hpp"

constexpr uint32_t SERIAL_RING_BUFFER_SIZE {256};
// #define SERIAL_RING_BUFFER_SIZE 128

class Serial {
	friend void serial1FriendIrq(void);
	public:
		void init(void);
		void println(const char *str);
		void printf(const char *fmt, ...);
		void write(const uint8_t data);
		void write(const uint8_t *data, int size);
		// void tick();
		inline bool hasPacket(void) const {
			return mDecoder.hasOutput();
		}
		inline ContorlRequestPacket fetchPacket(void) {
			return mDecoder.fetchOutput();
		}
		
	private:
		uint8_t mRingBuffer[SERIAL_RING_BUFFER_SIZE];
		uint8_t *mPushPtr;
		uint8_t *mPopPtr;
		uint8_t *M_BUFFER_END;
		bool isTransmitting;
		Decoder mDecoder;

		bool isRingBufferFull() const;
		bool isRingBufferEmpty() const;
		void irq();

};

extern Serial Serial1;


#endif

