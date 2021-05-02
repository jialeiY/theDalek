#include "hw/board.h"
#include "inc.h"

/***
 * 
 * Motor Connections
 * 
 *  ** Driver 1 ** 
 * AIN1 PD0
 * AIN2 PD1
 * BIN1 PD2
 * BIN2 PD3
 * PWMA PD12 (TIMER 4_1 AF(2))
 * PWMB PD13 (TIMER 4_2 AF(2))
 * 
 *  ** Driver 2 ** 
 * AIN1 PD4
 * AIN2 PD5
 * BIN1 PD6
 * BIN2 PD7
 * PWMA PD14 (TIMER 4_3 AF(2))
 * PWMB PD15 (TIMER 4_4 AF(2))
 * 
 *  ** Driver 3 ** 
 * AIN1 PD8
 * AIN2 PD9
 * BIN1 PD10
 * BIN2 PD11
 * PWMA PC8 (TIMER 3_3 AF(2))
 * PWMB PA15 (TIMER 2_1 AF(2))
 * 
 * 
 * 
 * ** LED **
 * led1 PC6 (Timer 3_1 AF(2), Timer 8_1 AF(3))
 * led2 PC7 (Timer 3_2 AF(2), Timer 8_2 AF(3))
 * Led3 PB9 (Timer 4_4 AF(2))
 * 
 * ** Buzzer **
 *  PE14 (Timer 1_4 AF(1))
 ***/

void boardInit(void) {


	// GPIO_SetBits(GPIOC, GPIO_Pin_6);
	// GPIOC->BSRRL = GPIO_Pin_6;
	// GPIO_ResetBits(GPIOC, GPIO_Pin_6);
}