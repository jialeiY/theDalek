#include "hw/board.h"
#include "inc.h"
#include "utils.hpp"

int foo(int a, int b) {
	return a + b;
}

void delay() {
	for (int i=0; i<80; ++i) {
		foo(i, i);
	}
}

#ifdef __cplusplus
 extern "C" {
#endif 


int main(void) {
	SysTick_Config(SystemCoreClock / 1000UL);
	boardInit();
	static uint32_t currentMillis {0UL};
	static bool on {false};

	while (true) {
		/*
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)) {
			GPIO_SetBits(GPIOC, GPIO_Pin_6);
		} else {
			GPIO_ResetBits(GPIOC, GPIO_Pin_6);
		}
		*/

		/*
		if (System::millis() - currentMillis > 50) {
			currentMillis = System::millis();
			if (on) {
				// GPIO_SetBits(GPIOC, GPIO_Pin_6);
			} else {
				// GPIO_ResetBits(GPIOC, GPIO_Pin_6);
			}
			on = !on;
		}
		*/
	}

	return 0;
}


#ifdef __cplusplus
 }
#endif 


