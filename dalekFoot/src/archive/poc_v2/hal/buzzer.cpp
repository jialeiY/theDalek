#include "ch.hpp"
#include "hal.h"
#include "hal/buzzer.h"
#include "hw/pwm_controller.h"


Buzzer::Buzzer(const PwmController &pwm): pwm_(pwm), isStopped_(true) {

}

void Buzzer::init(void) const {
	pwm_.init();
}

void Buzzer::tone(uint32_t freq) {
	if (isStopped_) {
		pwm_.init();
	}
	pwm_.setFreq(freq);
	pwm_.setValue(50);
}

void Buzzer::stop(void) {
	pwm_.clearPad();
	isStopped_ = true;
}
