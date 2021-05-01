#ifndef __HAL_LED__H__
#define __HAL_LED__H__

#include "ch.hpp"
#include "hal.h"
#include "hw/pwm_controller.h"

class Led {
	public:
		Led(const PwmController &pwm);
		void init(void) const;
		void setBrightness(pwmcnt_t value) const;
	private:
		const PwmController &pwm_;

};


#endif


