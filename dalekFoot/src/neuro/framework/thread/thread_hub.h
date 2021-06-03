#ifndef __FRAMEWORK_THREAD_THREAD_HUB_H__
#define __FRAMEWORK_THREAD_THREAD_HUB_H__

#include <string>
#include "framework/thread/event_type.h"
#include "framework/thread/i_thread.h"
#include <unordered_map>

namespace framework {
namespace thread {

class IThread;

class ThreadHub {
	public:
		ThreadHub();
		virtual ~ThreadHub();
		void registerThread(IThread *thread, const std::string &name);
		void notify(const std::string &threadName, EventType eventType, volatile void *data=nullptr) const;
	private:
		std::unordered_map<std::string, IThread *> mThreadMap;


};


}
}

#endif

