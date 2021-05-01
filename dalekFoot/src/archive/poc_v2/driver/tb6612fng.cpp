#include "driver/tb6612fng.h"
#include "ch.hpp"
#include "hal.h"


Tb6612fng::Tb6612fng(
	stm32_gpio_t * GPIO_PORT_AIN1,
	uint32_t GPIO_PAD_AIN1,
	stm32_gpio_t * GPIO_PORT_AIN2,
	uint32_t GPIO_PAD_AIN2,
	stm32_gpio_t * GPIO_PORT_BIN1,
	uint32_t GPIO_PAD_BIN1,
	stm32_gpio_t * GPIO_PORT_BIN2,
	uint32_t GPIO_PAD_BIN2,
	const PwmController &pwma,
	const PwmController &pwmb
): pad_ain1_(GPIO_PORT_AIN1, GPIO_PAD_AIN1),
	pad_ain2_(GPIO_PORT_AIN2, GPIO_PAD_AIN2),
	pad_bin1_(GPIO_PORT_BIN1, GPIO_PAD_BIN1),
	pad_bin2_(GPIO_PORT_BIN2, GPIO_PAD_BIN2),
	pwma_(pwma),
	pwmb_(pwmb) {
	palSetPadMode(pad_ain1_.port_, pad_ain1_.pad_, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(pad_ain2_.port_, pad_ain2_.pad_, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(pad_bin1_.port_, pad_bin1_.pad_, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(pad_bin2_.port_, pad_bin2_.pad_, PAL_MODE_OUTPUT_PUSHPULL);
	
	palClearPad(pad_ain1_.port_, pad_ain1_.pad_);
	palClearPad(pad_ain2_.port_, pad_ain2_.pad_);
	palClearPad(pad_bin1_.port_, pad_bin1_.pad_);
	palClearPad(pad_bin2_.port_, pad_bin2_.pad_);

}

void Tb6612fng::init(void) const{
	pwma_.init();
	pwmb_.init();
}

void Tb6612fng::on(void) const {
	// palSetPadMode(GPIOD, 12, 16);
	palSetPad(pad_ain1_.port_, pad_ain1_.pad_);
	palClearPad(pad_ain2_.port_, pad_ain2_.pad_);
	// palSetPad(pad_pwma_.port_, pad_pwma_.pad_);
	// pwmEnableChannel(&PWMD4, 0, 128);
	sdWrite(&SD1, (const uint8_t *)"on\r\n", 4);
}

void Tb6612fng::off(void) const {
	// palClearPad(pad_ain1_.port_, pad_ain1_.pad_);
	// palClearPad(pad_ain2_.port_, pad_ain2_.pad_);
	// palClearPad(pad_pwma_.port_, pad_pwma_.pad_);
	// pwmEnableChannel(&PWMD4, 0, 200);
}

void Tb6612fng::debug(int v) {
	pwma_.setValue(v);
}