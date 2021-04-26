#include "hw/pwm_controller.h"
#include "hw/board_def.h"


void PwmController::init() {
	pwmStart(kBoardDef.motor1APwmDriver, kBoardDef.motor1APwmConf);
	palSetPadMode(kBoardDef.motor1APort, kBoardDef.motor1APad, PAL_MODE_ALTERNATE(2));
}

void PwmController::setValue(pwmcnt_t value) {
	pwmEnableChannel(kBoardDef.motor1APwmDriver, kBoardDef.motor1APwmChannel, value);
}