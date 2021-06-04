#include "framework/rtdp/persistent/writer_thread.h"
#include <pthread.h>
#include <string>
#include <cstdio>
#include <unistd.h>


namespace framework {
namespace rtdp {
namespace persistent {


void* threadEntry(void *msg) {
	WriterThread *writer = (WriterThread *)msg;
	return writer->thread();
}


WriterThread::WriterThread() :	mIsStarted (false),
										mHardwareOutputPath {},
										mHardwareOutputFilePtr (nullptr) {
	pthread_mutex_init(&mMutex, NULL);
}

WriterThread::~WriterThread() {
	pthread_mutex_destroy(&mMutex);
}

void WriterThread::init()  {
	if (!mHardwareOutputPath.empty()) {
		mHardwareOutputFilePtr = fopen(mHardwareOutputPath.c_str(), "wb");
	}
}

void WriterThread::start() {
	pthread_create(&mPid, NULL, threadEntry, (void *)(this));
}


void WriterThread::stop() {

}

void * WriterThread::thread(void) {
	mIsStarted = true;
	while (true) {
		
		usleep(500ULL);
	}
	mIsStarted = false;
	return nullptr;
}

WriterThread writerThread;

}
}
}
