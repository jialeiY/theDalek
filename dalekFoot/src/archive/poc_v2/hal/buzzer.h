#ifndef __HAL_BUZZER_H__
#define __HAL_BUZZER_H__	

#include "ch.hpp"
#include "hal.h"
#include "hw/pwm_controller.h"

class Buzzer {
	public:
		Buzzer(const PwmController &pwm);
		void init(void) const;
		void tone(uint32_t freq);
		void stop(void);
	private:
		const PwmController &pwm_;
		bool isStopped_;

};


#endif


