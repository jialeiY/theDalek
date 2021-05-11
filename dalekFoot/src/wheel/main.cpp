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
		// Serial1.tick();
		if (Serial1.hasPacket()) {
			ContorlRequestPacket packet = Serial1.fetchPacket();
			Serial1.printf("got packet motor:%d %d %d %d, m:%d, led:%x\r\n", 
				packet.power[0], packet.power[1], packet.power[2], packet.power[3], packet.melodyIdx, packet.ledStatus);
		}
		/*
		if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9)) {
			GPIO_SetBits(GPIOC, GPIO_Pin_6);
		} else {
			GPIO_ResetBits(GPIOC, GPIO_Pin_6);
		}
		*/
		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis >= 10000) {
				
				currentMillis = System::millis();
				// USART_SendData(USART1, 0xC9);
				// USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			}
		}

		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis >= 5000) {
				// GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
				currentMillis = System::millis();
				// Serial1.println("12345678");

				
				Serial1.printf("time: %lu, enc: %ld\r\n", currentMillis, encoder3);

				// USART_SendData(USART1, 0xC9);
				// USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			}
		}

		/*
		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis >= 100) {
				currentMillis = System::millis();

				uint16_t adc1[8];
				uint16_t adc2[8];
				
				for (int i=0; i<8; ++i) {
					ADC_RegularChannelConfig(ADC1, static_cast<uint8_t>(i), 1, ADC_SampleTime_480Cycles);
					ADC_SoftwareStartConv(ADC1);
					// ADC_SoftwareStartConv(ADC2);
					while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {}
					adc1[i] = ADC_GetConversionValue(ADC1);
					// while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET) {}
					// adc2[i] = ADC_GetConversionValue(ADC2);
				}
				
				Serial1.printf("ADC1: \t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\r\n", adc1[0], adc1[1], adc1[2], adc1[3], adc1[4], adc1[5], adc1[6], adc1[7]);
				// Serial1.printf("ADC2: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", adc2[0], adc2[1], adc2[2], adc2[3], adc2[4], adc2[5], adc2[6], adc2[7]);
				Serial1.println("");
			}
		}
		*/
		{
			static uint32_t currentMillis {0UL};
			if (System::millis() - currentMillis >= 10000) {
				currentMillis = System::millis();

				extern volatile uint16_t adc1[8];
				extern volatile uint16_t adc2[8];
				extern volatile uint16_t adc2ex1[8];
				extern volatile uint16_t adc2ex2[8];
				extern volatile int count;
				volatile int cpCnt = count;
				count = 0;
				// extern uint16_t adc2[8];
				/*
				for (int i=0; i<8; ++i) {
					ADC_RegularChannelConfig(ADC1, static_cast<uint8_t>(i), 1, ADC_SampleTime_480Cycles);
					ADC_SoftwareStartConv(ADC1);
					// ADC_SoftwareStartConv(ADC2);
					while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {}
					adc1[i] = ADC_GetConversionValue(ADC1);
					// while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET) {}
					// adc2[i] = ADC_GetConversionValue(ADC2);
				}
				*/
				
				Serial1.printf("ADC1: \t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\r\n", adc1[0], adc1[1], adc1[2], adc1[3], adc1[4], adc1[5], adc1[6], adc1[7]);
				Serial1.printf("ADC2: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", adc2[0], adc2[1], adc2[2], adc2[3], adc2[4], adc2[5], adc2[6], adc2[7]);
				Serial1.printf("ADC1: \t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\r\n", adc2ex1[0], adc2ex1[1], adc2ex1[2], adc2ex1[3], adc2ex1[4], adc2ex1[5], adc2ex1[6], adc2ex1[7]);
				Serial1.printf("ADC2: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", adc2ex2[0], adc2ex2[1], adc2ex2[2], adc2ex2[3], adc2ex2[4], adc2ex2[5], adc2ex2[6], adc2ex2[7]);
				Serial1.printf("count:%d\r\n", cpCnt);
			}
		}
	}

	return 0;
}


#ifdef __cplusplus
 }
#endif 


