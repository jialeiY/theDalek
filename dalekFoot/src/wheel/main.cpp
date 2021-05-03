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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	static uint32_t currentMillis {0UL};
	static bool on {false};

	while (true) {
		if (System::millis() - currentMillis > 50) {
			currentMillis = System::millis();
			if (on) {
				GPIO_SetBits(GPIOC, GPIO_Pin_6);
			} else {
				GPIO_ResetBits(GPIOC, GPIO_Pin_6);
			}
			on = !on;
		}
	}

	return 0;
}
#ifdef __cplusplus
 }
#endif 


