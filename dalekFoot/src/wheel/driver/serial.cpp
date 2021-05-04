#include "driver/serial.h"


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
	
}

// This is utility for human print, no need for package sending
void Serial::println(const char *str) {
	while (*str) write(*(str++));
	write('\r');
	write('\n');
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
		USART_ReceiveData(USART1);
		// USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
	}
}

Serial Serial1;