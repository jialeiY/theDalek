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
#ifdef __cplusplus
}
#endif

#endif
