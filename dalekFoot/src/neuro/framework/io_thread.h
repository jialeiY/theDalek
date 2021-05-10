#ifndef __IO_THREAD_H__
#define __IO_THREAD_H__

#include "framework/i_thread.h"
#include "framework/watchdog_thread.h"

class IOThread : public IThread{
	public:
		IOThread(const ThreadHub &hub);
		virtual ~IOThread();
	protected:
		virtual void onNotify(uint64_t msgType);
	private:
		virtual void work();
};

#endif


