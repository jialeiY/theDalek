// #include "hw/board.h"
#include "inc.h"

int foo(int a, int b) {
	return a + b;
}

void delay() {
	for (int i=0; i<80; ++i) {
		foo(i, i);
	}
}

int main(void) {
	// SystemInit();
	// boardInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
	while (1) {
		GPIO_ResetBits(GPIOC, GPIO_Pin_6);
		
		for (int i=0; i<20; ++i) {
			delay();
		}
		
		GPIO_SetBits(GPIOC, GPIO_Pin_6);
	}
	return 0;
}
