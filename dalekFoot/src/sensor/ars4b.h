#ifndef __ARS4B_H__
#define __ARS4B_H__




class Radar {
	
};


#include <driver/can.h>


class Ars4b: public Radar {
	public:
		Ars4b();
		~Ars4b();
	private:
		Can mCan;
};


#endif

