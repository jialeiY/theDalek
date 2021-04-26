#ifndef __HW_BOARD_DEF_H__
#define __HW_BOARD_DEF_H__

#include "ch.h"
#include "hal.h"

struct Pin {
	stm32_gpio_t * port;
	uint32_t pad;
};


struct BoardDef {
	PWMConfig *motor1APwmConf;
	PWMDriver *motor1APwmDriver;
	pwmchannel_t motor1APwmChannel;
	stm32_gpio_t *motor1APort;
	uint32_t motor1APad;
	
};

extern BoardDef kBoardDef;

#endif


