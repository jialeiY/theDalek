#include "framework/rtdp/persistent/writer_thread.h"
#include "module/data_types/hardware_data.h"
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
	
}

WriterThread::~WriterThread() {
	
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

void WriterThread::doRequestWriteHardwareData(const data_types::HardwareData *data) {
	bool bufferSuccess = mHardwareDataQueue.push(data);
	if (!bufferSuccess) {
		printf("WARNING: cannot insert to hardware output buffer\r\n");
	}
}



void * WriterThread::thread(void) {
	mIsStarted = true;
	while (true) {
		if (mHardwareOutputFilePtr != nullptr) {
			if (!mHardwareDataQueue.isEmpty()) {
				data_types::HardwareData data;
				if (mHardwareDataQueue.pop(&data)) {
					fwrite(&data, sizeof(data_types::HardwareData), 1, mHardwareOutputFilePtr);
					fflush(mHardwareOutputFilePtr);
				} else {
					printf("WARNING: cannot pop data from buffer\r\n");
				}
			}
		}
		
		usleep(500ULL);
	}
	mIsStarted = false;
	return nullptr;
}



WriterThread writerThread;

}
}
}
