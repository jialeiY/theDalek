#include "framework/thread_hub.h"
#include "framework/event_type.h"


ThreadHub::ThreadHub() {

}


ThreadHub::~ThreadHub() {

}



void ThreadHub::registerThread(IThread *thread, const string &name) {
	mThreadMap[name] = thread;
}


void ThreadHub::notify(const string &threadName, EventType eventType) const{
	unordered_map<string, IThread *>::const_iterator iter = mThreadMap.find(threadName);
	if (iter != mThreadMap.end()) {
		iter->second->mPendingEvent = eventType;
	}
}


