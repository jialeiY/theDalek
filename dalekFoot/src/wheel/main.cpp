#include "hw/board.h"
#include "inc.h"
#include "utils/utils.hpp"
#include "utils/streams.hpp"
#include "driver/serial.hpp"
#include "driver/encoder.hpp"

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
	SystemCoreClockUpdate();
	boardInit();

	Serial1.init();
	
	static bool on {false};

	while (true) {
		/*
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)) {
			GPIO_SetBits(GPIOC, GPIO_Pin_6);
		} else {
			GPIO_ResetBits(GPIOC, GPIO_Pin_6);
		}
		*/
		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis > 100) {
				
				currentMillis = System::millis();
				// USART_SendData(USART1, 0xC9);
				// USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			}
		}

		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis > 500) {
				// GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
				currentMillis = System::millis();
				// Serial1.println("12345678");

				
				Serial1.printf("time: %lu, enc: %lu\r\n", currentMillis, encoder3);

				// USART_SendData(USART1, 0xC9);
				// USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			}
		}
			
	}

	return 0;
}


#ifdef __cplusplus
 }
#endif 


