#ifndef __IO_THREAD_H__
#define __IO_THREAD_H__

#include "framework/i_thread.h"
#include "framework/watchdog_thread.h"
#include "module/sensing/mcu_decoder/mcu_usart_decoder.h"

#include <cstdint>

class IOThread : public IThread {
	public:
		IOThread(const ThreadHub &hub);
		virtual ~IOThread();

	protected:
		virtual void onNotify(EventType eventType);

	private:
		enum IOStatus {
			TRANSCEIVING,
			WORKING,
			IDLE
		};
		IOStatus mStatus;
		int mTtyFd;
		
		std::uint8_t mOutputBuffer[9];
		std::uint8_t mInputBuffer[32];
		sensing::McuUsartDecoder mDecoder;
		virtual void work();
		void crcPayload();
};

#endif