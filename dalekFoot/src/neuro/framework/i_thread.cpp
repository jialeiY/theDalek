#include "framework/i_thread.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

namespace framework {

void* thread_entry(void *msg) {
	IThread *thread = (IThread *)msg;
	return thread->thread();
}


IThread::IThread(const ThreadHub &hub):mHub(hub), mPendingEvent(EventType::EMPTY) {
	pthread_mutex_init(&mMutex, NULL);

}

IThread::~IThread() {
	pthread_mutex_destroy(&mMutex);
}

void IThread::start() {
	pthread_create(&mPid, NULL, thread_entry, (void *)(this));
}

void IThread::stop() {
	
}
void *IThread::thread(void) {
	while (true) {
		if (mPendingEvent != EventType::EMPTY) {
			onNotify(mPendingEvent, mPendingData);
			mPendingEvent = EventType::EMPTY;
			mPendingData = nullptr;
		}
		work();
		// std::this_thread::sleep_for(std::chrono::nanoseconds(50));
	}
}

void IThread::notify(const string &threadName, EventType eventType, volatile void *data) {
	mHub.notify(threadName, eventType, data);
}


}