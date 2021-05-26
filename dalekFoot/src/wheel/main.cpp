#include "hw/board.h"
#include "inc.h"
#include "utils/utils.hpp"
#include "utils/streams.hpp"
#include "driver/serial.hpp"
#include "driver/encoder.hpp"
#include "modules/math/utility.h"
#include "driver/adc.hpp"


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


uint8_t replyPacketBuffer[51];


void transmitReplyPacket() {
	// Fetch data
	uint32_t millis = System::millis();
	uint32_t usec = 0;
	uint16_t encoderCpy[4];
	encoderCpy[0] = encoder1;
	encoderCpy[1] = encoder2;
	encoderCpy[2] = encoder3;
	encoderCpy[3] = encoder4;
	uint16_t fastAdcCpy[14];
	static uint8_t slowAdcIdx = 0;
	uint16_t slowAdcCpy;
	uint8_t userInputCpy = 0;
	for (int i=0; i<8; ++i) {
		fastAdcCpy[i] = adc1[i];
	}
	for (int i=0; i<6; ++i) {
		fastAdcCpy[8+i] = adc2[i];
	}
	if (slowAdcIdx < 8) {
		slowAdcCpy = adc2ex1[slowAdcIdx];
	} else {
		slowAdcCpy = adc2ex2[slowAdcIdx - 8];
	}

	// Write data into packet
	replyPacketBuffer[1] = uint8_t(0xFF & (millis >> 24));
	replyPacketBuffer[2] = uint8_t(0xFF & (millis >> 16));
	replyPacketBuffer[3] = uint8_t(0xFF & (millis >> 8));
	replyPacketBuffer[4] = uint8_t(0xFF & millis);

	replyPacketBuffer[5] = uint8_t(0xFF & (usec >> 24));
	replyPacketBuffer[6] = uint8_t(0xFF & (usec >> 16));
	replyPacketBuffer[7] = uint8_t(0xFF & (usec >> 8));
	replyPacketBuffer[8] = uint8_t(0xFF & usec);

	for (int i=0; i<4; ++i) {
		replyPacketBuffer[9 + i*2] = uint8_t(0xFF & (encoderCpy[i] >> 8));
		replyPacketBuffer[10 + i*2] = uint8_t(0xFF & encoderCpy[i]);
	}
	
	for (int i=0; i<14; ++i) {
		replyPacketBuffer[17 + i*2] = uint8_t(0xFF & (fastAdcCpy[i] >> 8));
		replyPacketBuffer[18 + i*2] = uint8_t(0xFF & fastAdcCpy[i]);
	}
	replyPacketBuffer[45] = slowAdcIdx;
	replyPacketBuffer[46] = uint8_t(0xFF & (slowAdcCpy >> 8));
	replyPacketBuffer[47] = uint8_t(0xFF & slowAdcCpy);
	replyPacketBuffer[48] = userInputCpy;
	replyPacketBuffer[49] = crc8(replyPacketBuffer + 1, 48);

	Serial1.write(replyPacketBuffer, 51);

	// Update
	slowAdcIdx++;
	if (slowAdcIdx >= 16) slowAdcIdx = 0;
	

}

TIM_OCInitTypeDef TIM_OCStruct;
void setSpeed(int32_t speed) {
	
	if (speed < 0) {

	} else if (speed > 0) {
		TIM_OCStruct.TIM_Pulse = speed;
		TIM_OC1Init(TIM4, &TIM_OCStruct);
		
	} else { // speed == 0

	}
}

int main(void) {
	SysTick_Config(SystemCoreClock / 1000UL);
	SystemCoreClockUpdate();
	boardInit();
	Serial1.init();
	// motor init

	TIM_OCStructInit(&TIM_OCStruct);
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OutputNState = TIM_OCPolarity_High;


	replyPacketBuffer[0] = 0x55;
	replyPacketBuffer[50] = 0xAA;
	
	static bool on {false};

	bool isDebugMode = (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);

	while (true) {
		// Serial1.tick();
		if (Serial1.hasPacket()) {
			GPIO_SetBits(GPIOC, GPIO_Pin_6);
			
			transmitReplyPacket();
			GPIO_ResetBits(GPIOC, GPIO_Pin_6);
			
			ContorlRequestPacket packet = Serial1.fetchPacket();
			if (isDebugMode) {
				Serial1.printf("got packet motor:%d %d %d %d, m:%d, led:%x\r\n", 
					packet.power[0], packet.power[1], packet.power[2], packet.power[3], packet.melodyIdx, packet.ledStatus);
			}
			setSpeed(static_cast<int32_t>(packet.power[3]) * 4);
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
			if (System::millis() - currentMillis >= 20000) {
				// GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
				currentMillis = System::millis();
				// Serial1.println("12345678");

				if (isDebugMode) {
					Serial1.printf("time: %lu, enc: %ld\r\n", currentMillis, encoder3);
				}

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
			if (System::millis() - currentMillis >= 1000) {
				currentMillis = System::millis();


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
				if (isDebugMode) {
					Serial1.printf("ADC1: \t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\r\n", adc1[0], adc1[1], adc1[2], adc1[3], adc1[4], adc1[5], adc1[6], adc1[7]);
					Serial1.printf("ADC2: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", adc2[0], adc2[1], adc2[2], adc2[3], adc2[4], adc2[5], adc2[6], adc2[7]);
					Serial1.printf("ADC1: \t%u\t%u\t%u\t%u\t%u\t%u\t%u\t%u\r\n", adc2ex1[0], adc2ex1[1], adc2ex1[2], adc2ex1[3], adc2ex1[4], adc2ex1[5], adc2ex1[6], adc2ex1[7]);
					Serial1.printf("ADC2: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", adc2ex2[0], adc2ex2[1], adc2ex2[2], adc2ex2[3], adc2ex2[4], adc2ex2[5], adc2ex2[6], adc2ex2[7]);
					Serial1.printf("encoder: %d %d %d %d\r\n", encoder1, encoder2, encoder3, encoder4);
					Serial1.printf("count:%d button: %d\r\n\r\n", cpCnt, GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4));
				}
			}
		}
	}

	return 0;
}


#ifdef __cplusplus
 }
#endif 


