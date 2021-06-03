#include "framework/thread/thread_hub.h"
#include "framework/thread/event_type.h"

namespace framework {
namespace thread {

ThreadHub::ThreadHub() {

}


ThreadHub::~ThreadHub() {

}



void ThreadHub::registerThread(IThread *thread, const std::string &name) {
	mThreadMap[name] = thread;
}


void ThreadHub::notify(const std::string &threadName, EventType eventType, volatile void *data) const{
	std::unordered_map<std::string, IThread *>::const_iterator iter = mThreadMap.find(threadName);
	if (iter != mThreadMap.end()) {
		iter->second->mPendingData = data;
		iter->second->mPendingEvent = eventType;
	}
}

}
}
