#ifndef __FRAMEWORK_WATCHDOG_THREAD_H__
#define __FRAMEWORK_WATCHDOG_THREAD_H__


#include <pthread.h>
#include "framework/i_thread.h"

class WatchdogThread : public IThread{
	public:
		WatchdogThread(const ThreadHub &hub);
		virtual ~WatchdogThread();
	protected:
		virtual void onNotify(uint64_t msgType);
	private:
		virtual void work();
};


#endif

