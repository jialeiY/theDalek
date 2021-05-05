/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <stdint.h>

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

volatile uint32_t gMillis = 0;
void SysTick_Handler(void)
{
	gMillis ++;
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


volatile int32_t encoder3 = 0UL;
volatile uint8_t encoder3A = 0;  // C9
volatile uint8_t encoder3B = 0;  // A8

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line8) != RESET) { // A8
		EXTI_ClearITPendingBit(EXTI_Line8);
		encoder3B = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
		if (encoder3A) {
			encoder3 += encoder3B ? -1 : 1;
		} else {
			encoder3 += encoder3B ? 1 : -1;
		}
	} else if (EXTI_GetITStatus(EXTI_Line9) != RESET) { // C9
		EXTI_ClearITPendingBit(EXTI_Line9);
		encoder3A = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
		if (encoder3B) {
			encoder3 += encoder3A ? 1 : -1;
		} else {
			encoder3 += encoder3A ? -1 : 1;
		}
	}
}

void usart1irq(void);
void USART1_IRQHandler(void) {
	usart1irq();
}

volatile uint16_t adc1[8];
static volatile uint8_t adc1Ch = 0U;
volatile uint16_t adc2[8];
static volatile uint8_t adc2Ch = 0U;
volatile int count = 0;
void ADC_IRQHandler(void) {
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET) {
		// GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
		adc1[adc1Ch] = ADC_GetConversionValue(ADC1);
		adc1Ch ++;
		adc1Ch &= 0x07;
		count ++;
		ADC_RegularChannelConfig(ADC1, adc1Ch, 1, ADC_SampleTime_480Cycles);
		ADC_SoftwareStartConv(ADC1);
		// ADC_ClearITPendingBit(ADC1,ADC_FLAG_EOC);//<--clear automatically
	}
	
	if(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) != RESET) {
		GPIO_ToggleBits(GPIOC, GPIO_Pin_7);
		adc2[adc2Ch] = ADC_GetConversionValue(ADC2);
		adc2Ch ++;
		adc2Ch &= 0x07;
		count ++;
		ADC_RegularChannelConfig(ADC2, adc2Ch, 1, ADC_SampleTime_480Cycles);
		ADC_SoftwareStartConv(ADC2);
	}
}