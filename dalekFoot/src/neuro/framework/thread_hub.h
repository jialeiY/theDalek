#ifndef __FRAMEWORK_THREAD_HUB_H__
#define __FRAMEWORK_THREAD_HUB_H__

#include <string>
#include "framework/i_thread.h"
#include <unordered_map>

using namespace std;

class IThread;

class ThreadHub {
	public:
		ThreadHub();
		virtual ~ThreadHub();
		void registerThread(IThread *thread, const string &name);
		void notify(const string &threadName, uint64_t msgType) const;
	private:
		unordered_map<string, IThread *> mThreadMap;


};

#endif

