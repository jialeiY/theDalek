#ifndef __FRAMEWORK_THREAD_HUB_H__
#define __FRAMEWORK_THREAD_HUB_H__

#include <string>
#include "framework/event_type.h"
#include "framework/i_thread.h"
#include <unordered_map>

namespace framework {

class IThread;

class ThreadHub {
	public:
		ThreadHub();
		virtual ~ThreadHub();
		void registerThread(IThread *thread, const std::string &name);
		void notify(const std::string &threadName, EventType eventType, void *data=nullptr) const;
	private:
		std::unordered_map<std::string, IThread *> mThreadMap;


};


}
#endif

