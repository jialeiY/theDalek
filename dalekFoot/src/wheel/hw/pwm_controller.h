#ifndef __HW_PWM_CONTROLLER_H__
#define __HW_PWM_CONTROLLER_H__


#include "ch.hpp"
#include "hal.h"




class PwmController {
	public:
		void init();
		void setValue(pwmcnt_t value);
};



#endif


