#ifndef __ARS4B_H__
#define __ARS4B_H__


#include <driver/can.h>

class Radar {
	public:
		Radar() {}
		virtual ~Radar() {}

		virtual void work() = 0;
};


class Ars4b: public Radar {
	public:
		explicit Ars4b();
		virtual ~Ars4b();

		virtual void work() {
			mCan->sendMessage();
		}

	private:
		Can *mCan;
		
};


#endif

