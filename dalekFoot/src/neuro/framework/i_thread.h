#ifndef __FRAMEWORK_I_THREAD_H__
#define __FRAMEWORK_I_THREAD_H__


#include <pthread.h>
#include <cstdint>
#include <string>
#include "event_type.h"
#include "framework/thread_hub.h"

using namespace std;
class ThreadHub;

class IThread {
	public:
		IThread(const ThreadHub &hub);
		virtual ~IThread();
		void start();
		void stop();
		
	protected:
		virtual void onNotify(uint64_t msgType) = 0;
		void notify(const string &threadName, EventType eventType);

	private:
		pthread_mutex_t mMutex;
		pthread_t mPid;
		friend void * thread_entry(void*);
		void *thread(void);
		virtual void work() = 0;
		const ThreadHub &mHub;
		friend ThreadHub;
		volatile EventType mPendingEvent;
};


#endif

