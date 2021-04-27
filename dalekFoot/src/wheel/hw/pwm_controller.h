#ifndef __HW_PWM_CONTROLLER_H__
#define __HW_PWM_CONTROLLER_H__


#include "ch.hpp"
#include "hal.h"




class PwmController {
	public:
		PwmController(PWMDriver * const pwmDriver, pwmchannel_t const pwmChannel, PWMConfig * const pwmConf, stm32_gpio_t * const port, uint32_t const pad, int const afn);
		void init() const;
		void setValue(pwmcnt_t value) const;
		void setFreq(uint32_t freq) const;
		void clearPad(void) const;
		
	private:
		PWMDriver * const pwmDriver_;
		pwmchannel_t const pwmChannel_;
		PWMConfig * const pwmConf_;
		stm32_gpio_t * const port_;
		uint32_t const pad_;
		int const afn_;

};



#endif


