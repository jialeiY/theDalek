#include "driver/serial.hpp"
#include "utils/streams.hpp"
#include "modules/decoder/decoder.hpp"
#include <stdarg.h>

inline void serial1FriendIrq(void) {
	Serial1.irq();
}
extern "C" {
	void usart1irq(void) {
		serial1FriendIrq();
	}
}


void Serial::init(void) {
	mPushPtr = mRingBuffer;
	mPopPtr = mRingBuffer;
	M_BUFFER_END = mRingBuffer + SERIAL_RING_BUFFER_SIZE;
	if (M_BUFFER_END != (mRingBuffer+SERIAL_RING_BUFFER_SIZE)) GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
	isTransmitting = false;
	mDecoder.init();
}

// This is utility for human print, no need for package sending
void Serial::println(const char *str) {
	while (*str) write(*(str++));
	write('\r');
	write('\n');
}


void Serial::printf(const char *fmt, ...) {
	char buffer[128];
	va_list ap;
  int formatted_bytes;
  va_start(ap, fmt);
  formatted_bytes = cooboc::vsprintf(buffer, fmt, ap);
  va_end(ap);
	for (int i=0; i<formatted_bytes; ++i) {
		write(buffer[i]);
	}
}


inline void Serial::write(const uint8_t data) {
	// TODO: no need to block all irq, only usart related is enough
	__disable_irq();
	if (isTransmitting) {
		// check buffer is empty
		if (!isRingBufferFull()) {
			// Push a data into buffer
			*mPushPtr = data;
			mPushPtr ++;
			if (mPushPtr >= M_BUFFER_END) mPushPtr = mRingBuffer;
		}
	} else {
		USART_SendData(USART1, data);
		isTransmitting = true;
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	__enable_irq();
}

void Serial::write(const uint8_t *data, int size) {
	for (int i=0; i<size; ++i) {
		write(data[i]);
	}
}


inline bool Serial::isRingBufferFull() const {
	return ((mPopPtr == mRingBuffer) && (mPushPtr == (M_BUFFER_END-1)))
			|| ((mPushPtr + 1) == mPopPtr);
}

inline bool Serial::isRingBufferEmpty() const {
	return mPushPtr == mPopPtr;
}

inline void Serial::irq() {
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET) {
		if (isRingBufferEmpty()) {
			isTransmitting = false;
			USART_ClearITPendingBit(USART1, USART_IT_TXE);
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		} else {
			USART_SendData(USART1, *mPopPtr);
			mPopPtr++;
			if (mPopPtr >= M_BUFFER_END) mPopPtr = mRingBuffer;
		}
	} else {
		mDecoder.decode(uint8_t(USART_ReceiveData(USART1)));
		// USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
	}
}

Serial Serial1;