#include "hw/pwm_controller.h"
#include "hw/board_def.h"

PwmController::PwmController(PWMDriver * const pwmDriver, pwmchannel_t const pwmChannel, PWMConfig * const pwmConf, stm32_gpio_t * const port, uint32_t const pad)
	: pwmDriver_(pwmDriver),
		pwmChannel_(pwmChannel),
		pwmConf_(pwmConf),
		port_(port),
		pad_(pad) {
	
}

void PwmController::init() const {
	pwmStart(pwmDriver_, pwmConf_);
	palSetPadMode(port_, pad_, PAL_MODE_ALTERNATE(2));
}

void PwmController::setValue(pwmcnt_t value) const {
	pwmEnableChannel(pwmDriver_, pwmChannel_, value);
}