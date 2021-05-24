#ifndef __FRAMEWORK_CONTROL_THREAD_H__
#define __FRAMEWORK_CONTROL_THREAD_H__

#include "framework/i_thread.h"

namespace framework {

class ControlThread : public IThread {
	public:
		ControlThread(const ThreadHub &hub);
		virtual ~ControlThread();

	protected:
		virtual void onNotify(EventType msgType, void *data=nullptr);

	private:
		virtual void work();
};

}


#endif
