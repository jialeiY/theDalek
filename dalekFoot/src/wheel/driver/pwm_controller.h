#ifndef __DRIVER_PWM_CONTROLLER_H__
#define __DRIVER_PWM_CONTROLLER_H__


#include "ch.hpp"
#include "hal.h"




class PwmController {
	public:
		~PwmController();
		static PwmController &get() {
			static PwmController pwmController;
			return pwmController;
		}
	private:
		PwmController();
};



#endif


