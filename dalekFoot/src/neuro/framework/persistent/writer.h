#ifndef __FRAMEWORK_PERSISTENT_WRITER_H__
#define __FRAMEWORK_PERSISTENT_WRITER_H__


#include <pthread.h>
#include <string>
#include <cstdio>


namespace framework {
namespace persistent {

class Writer {
	public:
		Writer();
		virtual ~Writer();
		void setHardwareOutputPath(const std::string & filepath) {
			mHardwareOutputPath = filepath;
		}
		void init(void);
		void start(void);
		void stop(void);
		inline bool isStarted(void) const {return mIsStarted;}
	private:
		friend void *threadEntry(void *);
		void *thread(void);
		pthread_mutex_t mMutex;
		pthread_t mPid;
		volatile bool mIsStarted;
		std::string mHardwareOutputPath;
		FILE *mHardwareOutputFilePtr;
};

}
}


#endif

