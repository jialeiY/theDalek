#include "hw/pwm_controller.h"
#include "hw/board_def.h"

#include "ch.h"
#include "hal.h"

PwmController::PwmController(PWMDriver * const pwmDriver, pwmchannel_t const pwmChannel, PWMConfig * const pwmConf, stm32_gpio_t * const port, uint32_t const pad, int const afn)
	: pwmDriver_(pwmDriver),
		pwmChannel_(pwmChannel),
		pwmConf_(pwmConf),
		port_(port),
		pad_(pad),
		afn_(afn) {
	
}

void PwmController::init() const {
	pwmStart(pwmDriver_, pwmConf_);
	palSetPadMode(port_, pad_, PAL_MODE_ALTERNATE(afn_));
}

void PwmController::setValue(pwmcnt_t value) const {
	pwmEnableChannel(pwmDriver_, pwmChannel_, value);
}


void PwmController::setFreq(uint32_t freq) const {
	pwmConf_->frequency = freq;
	pwmStart(pwmDriver_, pwmConf_);
}

void PwmController::clearPad(void) const {
	palSetPadMode(port_, pad_, PAL_MODE_OUTPUT_OPENDRAIN);
	palClearPad(port_, pad_);
}