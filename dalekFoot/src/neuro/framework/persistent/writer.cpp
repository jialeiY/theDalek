#include "framework/persistent/writer.h"
#include <pthread.h>
#include <string>
#include <cstdio>
#include <unistd.h>


namespace framework {
namespace persistent {



void* threadEntry(void *msg) {
	Writer *writer = (Writer *)msg;
	return writer->thread();
}


Writer::Writer() :	mIsStarted (false),
										mHardwareOutputPath {},
										mHardwareOutputFilePtr (nullptr) {
	pthread_mutex_init(&mMutex, NULL);
}

Writer::~Writer() {
	pthread_mutex_destroy(&mMutex);
}

void Writer::init()  {
	if (!mHardwareOutputPath.empty()) {
		mHardwareOutputFilePtr = fopen(mHardwareOutputPath.c_str(), "wb");
	}
}

void Writer::start() {
	pthread_create(&mPid, NULL, threadEntry, (void *)(this));
}


void Writer::stop() {

}

void * Writer::thread(void) {
	mIsStarted = true;
	while (true) {
		
		usleep(500ULL);
	}
	mIsStarted = false;
	return nullptr;
}



}
}
