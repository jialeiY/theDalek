#ifndef __FRAMEWORK_WATCHDOG_THREAD_H__
#define __FRAMEWORK_WATCHDOG_THREAD_H__

#include "framework/i_thread.h"

class WatchdogThread : public IThread {
	public:
		WatchdogThread(const ThreadHub &hub);
		virtual ~WatchdogThread();

	protected:
		virtual void onNotify(EventType msgType);

	private:
		virtual void work();
};

#endif
