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
	pwmStart(kBoardDef.motor1APwmDriver, kBoardDef.motor1APwmConf);
	palSetPadMode(kBoardDef.motor1APort, kBoardDef.motor1APad, PAL_MODE_ALTERNATE(2));
}

void PwmController::setValue(pwmcnt_t value) const {
	pwmEnableChannel(kBoardDef.motor1APwmDriver, kBoardDef.motor1APwmChannel, value);
}