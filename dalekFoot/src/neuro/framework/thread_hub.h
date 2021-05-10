#ifndef __FRAMEWORK_THREAD_HUB_H__
#define __FRAMEWORK_THREAD_HUB_H__

#include <string>
#include "framework/event_type.h"
#include "framework/i_thread.h"
#include <unordered_map>

using namespace std;

class IThread;

class ThreadHub {
	public:
		ThreadHub();
		virtual ~ThreadHub();
		void registerThread(IThread *thread, const string &name);
		void notify(const string &threadName, EventType eventType) const;
	private:
		unordered_map<string, IThread *> mThreadMap;


};

#endif

