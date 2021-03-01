#ifndef __ARS4B_H__
#define __ARS4B_H__


#include <driver/can.h>

class Radar {
	public:
		Radar() {}
		virtual ~Radar() {}
};


class Ars4b: public Radar {
	public:
		explicit Ars4b();
		virtual ~Ars4b();
	private:
		Can *mCan;
		
};


#endif

