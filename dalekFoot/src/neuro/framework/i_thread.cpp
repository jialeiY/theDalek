#include "framework/i_thread.h"
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;


void* thread_entry(void *msg) {
	IThread *wdt = (IThread *)msg;
	wdt->work();
	return NULL;
}


IThread::IThread(const ThreadHub &hub):mHub(hub) {
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


void IThread::notify(const string &threadName, uint64_t msgType) {
	mHub.notify(threadName, msgType);
}
