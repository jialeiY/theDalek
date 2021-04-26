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
	
};

extern BoardDef kBoardDef;

#endif


