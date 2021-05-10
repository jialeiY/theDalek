#ifndef __FRAMEWORK_I_THREAD_H__
#define __FRAMEWORK_I_THREAD_H__


#include <pthread.h>
#include <cstdint>
#include <string>

using namespace std;
#include "framework/thread_hub.h"
class ThreadHub;

class IThread {
	public:
		IThread(const ThreadHub &hub);
		virtual ~IThread();
		void start();
		void stop();
		
	protected:
		virtual void onNotify(uint64_t msgType) = 0;
		void notify(const string &threadName, uint64_t msgType);

	private:
		pthread_mutex_t mMutex;
		pthread_t mPid;
		friend void * thread_entry(void*);
		virtual void work() = 0;
		const ThreadHub &mHub;
		friend ThreadHub;
};


#endif

