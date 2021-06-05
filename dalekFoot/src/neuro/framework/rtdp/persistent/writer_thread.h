#ifndef __FRAMEWORK_RTDP_PERSISTENT_WRITER_THREAD_H__
#define __FRAMEWORK_RTDP_PERSISTENT_WRITER_THREAD_H__

#include "module/data_types/hardware_data.h"
#include "parameter.h"

#include <pthread.h>
#include <string>
#include <cstdio>
#include <array>
#include <cstring>


namespace framework {
namespace rtdp {
namespace persistent {

/// @todo: move utility class into standalone file
template<typename T, std::size_t size>
class SafeCircularQueue {
	public:
		SafeCircularQueue() : mPushOffset(0U),
													mPopOffset(0U) {
			pthread_mutex_init(&mMutex, NULL);
		}

		virtual ~SafeCircularQueue() {
			pthread_mutex_destroy(&mMutex);
		}

		inline bool isFull(void) {
			pthread_mutex_lock(&mMutex);
			bool result = lockedIsFull();
			pthread_mutex_unlock(&mMutex);
			return result;
		}

		bool push(const T *data) {
			bool success = false;
			pthread_mutex_lock(&mMutex);
			if (!lockedIsFull()) {
				memcpy(mBuffer+mPushOffset, data, sizeof(T));
				mPushOffset++;
				mPushOffset %= size;
				success = true;
			}
			pthread_mutex_unlock(&mMutex);
			return success;
		}

		inline bool isEmpty(void) {
			bool result = false;
			pthread_mutex_lock(&mMutex);
			result = lockIsEmpty();
			pthread_mutex_unlock(&mMutex);
			return result;
		}

		bool pop(T *dest) {
			bool success = false;
			pthread_mutex_lock(&mMutex);
			if (!lockIsEmpty()) {
				memcpy(mBuffer+mPopOffset, dest, sizeof(T));
				mPopOffset++;
				mPopOffset %= size;
				success = true;
			}
			pthread_mutex_unlock(&mMutex);
			return success;
		}
	private:
		T mBuffer[size];
		std::size_t mPushOffset;
		std::size_t mPopOffset;
		pthread_mutex_t mMutex;

		inline bool lockedIsFull(void) const {
			bool result = false;
			if ((mPushOffset + 1) == mPopOffset) result = true;
			if ((mPopOffset == 0) && (mPushOffset == size - 1)) result = true;
			return result;
		}

		inline bool lockIsEmpty(void) const {
			return mPopOffset == mPushOffset;
		}
};

class WriterThread {
	public:
		WriterThread();
		virtual ~WriterThread();
		void setHardwareOutputPath(const std::string & filepath) {
			mHardwareOutputPath = filepath;
		}
		void init(void);
		void start(void);
		void stop(void);
		inline bool isStarted(void) const {return mIsStarted;}

		inline void requestWriteHardwareData(const data_types::HardwareData *data) {
			if (mIsStarted) {
				doRequestWriteHardwareData(data);
			}
		}
	private:
		friend void *threadEntry(void *);
		void *thread(void);
		
		pthread_t mPid;
		volatile bool mIsStarted;
		std::string mHardwareOutputPath;
		FILE *mHardwareOutputFilePtr;
		SafeCircularQueue<data_types::HardwareData, kPersistentWriterBufferSize> mHardwareDataQueue;
		

		void doRequestWriteHardwareData(const data_types::HardwareData *data);
		
};

extern WriterThread writerThread;

}
}
}

#endif

