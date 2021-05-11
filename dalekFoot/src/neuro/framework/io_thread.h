#ifndef __IO_THREAD_H__
#define __IO_THREAD_H__

#include "framework/i_thread.h"
#include "framework/watchdog_thread.h"
#include <cstdint>

class IOThread : public IThread {
	public:
		IOThread(const ThreadHub &hub);
		virtual ~IOThread();

	protected:
		virtual void onNotify(EventType eventType);

	private:
		int mTtyFd;

		std::uint8_t mOutputBuffer[9];

		virtual void work();
		void crcPayload();
};

#endif
