#ifndef __FRAMEWORK_LOOP_THREAD_H__
#define __FRAMEWORK_LOOP_THREAD_H__

#include "framework/i_thread.h"
#include <cstdint>

namespace framework {

class LoopThread : public IThread {
	public:
		LoopThread(const ThreadHub &hub);
		virtual ~LoopThread();
	protected:
		virtual void onNotify(EventType msgType, volatile void *data = nullptr);
		virtual void work();
	private:
		enum LoopStatus {
			WORKING,
			WAITTING
		};
		LoopStatus mStatus;
		std::uint64_t mCycleStartTime;

		void tickOnWaitting(const std::uint64_t &currentTime);
		void tickOnWorking(const std::uint64_t &currentTime);
};

}

#endif

