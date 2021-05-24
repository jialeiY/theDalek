#include "framework/thread_hub.h"
#include "framework/event_type.h"

namespace framework {

ThreadHub::ThreadHub() {

}


ThreadHub::~ThreadHub() {

}



void ThreadHub::registerThread(IThread *thread, const std::string &name) {
	mThreadMap[name] = thread;
}


void ThreadHub::notify(const std::string &threadName, EventType eventType, void *data) const{
	std::unordered_map<std::string, IThread *>::const_iterator iter = mThreadMap.find(threadName);
	if (iter != mThreadMap.end()) {
		iter->second->mPendingEvent = eventType;
	}
}

}
