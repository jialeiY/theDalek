#include "framework/i_thread.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;


void* thread_entry(void *msg) {
	IThread *wdt = (IThread *)msg;
	return wdt->thread();
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
			onNotify(mPendingEvent);
			mPendingEvent = EventType::EMPTY;
		}
		work();
	}
}

void IThread::notify(const string &threadName, EventType eventType) {
	mHub.notify(threadName, eventType);
}
