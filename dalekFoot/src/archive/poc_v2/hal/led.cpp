#include "hal/led.h"

Led::Led(const PwmController &pwm) : pwm_(pwm) {

}

void Led::init(void) const {
	pwm_.init();
}

void Led::setBrightness(pwmcnt_t value) const {
	pwm_.setValue(value);
}