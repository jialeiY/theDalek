#ifndef __FRAMEWORK_LOOP_THREAD_H__
#define __FRAMEWORK_LOOP_THREAD_H__

#include "framework/i_thread.h"

namespace framework {

class LoopThread : public IThread {
	public:
		LoopThread(const ThreadHub &hub);
		virtual ~LoopThread();
	protected:
		virtual void onNotify(EventType msgType, volatile void *data = nullptr);
		virtual void work();
	private:

};

}

#endif

