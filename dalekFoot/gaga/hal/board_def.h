#ifndef __HAL_BOARD_DEF_H__
#define __HAL_BOARD_DEF_H__

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif
extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/** For Debug only **/
#define LED1_PORT GPIOC
#define LED1_PIN  GPIO_PIN_6

#define LED2_PORT GPIOC
#define LED2_PIN  GPIO_PIN_7

#define LED1_ON     HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET)
#define LED1_OFF    HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET)
#define LED1_TOGGLE HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN)

#define LED2_ON     HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET)
#define LED2_OFF    HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET)
#define LED2_TOGGLE HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN)

#ifdef __cplusplus
}
#endif

#endif
