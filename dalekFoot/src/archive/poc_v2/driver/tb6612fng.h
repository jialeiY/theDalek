#ifndef __DRIVER_TB6612FNG_H__
#define __DRIVER_TB6612FNG_H__


#include "ch.hpp"
#include "hal.h"

#include "hw/pwm_controller.h"

struct Pad {
	stm32_gpio_t * port_;
	uint32_t pad_;
	Pad(stm32_gpio_t *port, uint32_t pad): port_(port), pad_(pad) {}
};

class Tb6612fng {
	public:
		Tb6612fng(
			stm32_gpio_t * const GPIO_PORT_AIN1,
			uint32_t const GPIO_PAD_AIN1,
			stm32_gpio_t * const GPIO_PORT_AIN2,
			uint32_t const GPIO_PAD_AIN2,
			stm32_gpio_t * const GPIO_PORT_BIN1,
			uint32_t const GPIO_PAD_BIN1,
			stm32_gpio_t * const GPIO_PORT_BIN2,
			uint32_t const GPIO_PAD_BIN2,
			const PwmController &pwma,
			const PwmController &pwmb
		);
		void init(void) const;
		void on(void) const;
		void off(void) const;
		void debug(int v);
	private:
		Pad pad_ain1_;
		Pad pad_ain2_;
		Pad pad_bin1_;
		Pad pad_bin2_;

		const PwmController &pwma_;
		const PwmController &pwmb_;
};


#endif