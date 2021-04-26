#ifndef __HW_PWM_CONTROLLER_H__
#define __HW_PWM_CONTROLLER_H__


#include "ch.hpp"
#include "hal.h"




class PwmController {
	public:
		PwmController(PWMDriver * const pwmDriver, pwmchannel_t const pwmChannel, PWMConfig * const pwmConf, stm32_gpio_t * const port, uint32_t const pad);
		void init() const;
		void setValue(pwmcnt_t value) const;
	private:
		PWMDriver * const pwmDriver_;
		pwmchannel_t const pwmChannel_;
		PWMConfig * const pwmConf_;
		stm32_gpio_t * const port_;
		uint32_t const pad_;

};



#endif


