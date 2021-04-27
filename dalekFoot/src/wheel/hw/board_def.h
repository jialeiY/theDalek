#ifndef __HW_BOARD_DEF_H__
#define __HW_BOARD_DEF_H__

#include "ch.h"
#include "hal.h"

struct Pin {
	stm32_gpio_t * port;
	uint32_t pad;
};


struct BoardDef {
	PWMDriver *motor1APwmDriver;
	pwmchannel_t motor1APwmChannel;
	PWMConfig *motor1APwmConf;
	stm32_gpio_t *motor1APort;
	uint32_t motor1APad;

	PWMDriver *motor1BPwmDriver;
	pwmchannel_t motor1BPwmChannel;
	PWMConfig *motor1BPwmConf;
	stm32_gpio_t *motor1BPort;
	uint32_t motor1BPad;

	PWMDriver *led1PwmDriver;
	pwmchannel_t led1PwmChannel;
	PWMConfig *led1PwmConf;
	stm32_gpio_t *led1Port;
	uint32_t led1Pad;

	PWMDriver *led2PwmDriver;
	pwmchannel_t led2PwmChannel;
	PWMConfig *led2PwmConf;
	stm32_gpio_t *led2Port;
	uint32_t led2Pad;

	PWMDriver *led3PwmDriver;
	pwmchannel_t led3PwmChannel;
	PWMConfig *led3PwmConf;
	stm32_gpio_t *led3Port;
	uint32_t led3Pad;

};

extern BoardDef kBoardDef;

#endif


