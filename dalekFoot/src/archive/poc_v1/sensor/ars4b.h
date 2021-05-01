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
			uint8_t data[8] {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
			mCan->sendStandardMessage(0x5A, data, 8);
		}

	private:
		Can *mCan;
		
};


#endif

