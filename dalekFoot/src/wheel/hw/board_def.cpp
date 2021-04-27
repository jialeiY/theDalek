#include "hw/board_def.h"
#include "ch.h"
#include "hal.h"





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

static PWMConfig pwm1Cfg {
	20000,
	100,                                  /* Initial PWM period 1S.         */
	NULL,                                     /* Period callback.               */
	{
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},          		/* CH1 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH2 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH3 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL}              /* CH4 mode and callback.         */
	},
	0,                                        /* Control Register 2.            */
	0                                         /* DMA/Interrupt Enable Register. */
};

static PWMConfig pwm3Cfg {
	5120000,
	256,                                  		/* Initial PWM period 1S.         */
	NULL,                                     /* Period callback.               */
	{
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},          		/* CH1 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH2 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH3 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL}              /* CH4 mode and callback.         */
	},
	0,                                        /* Control Register 2.            */
	0                                         /* DMA/Interrupt Enable Register. */
};

static PWMConfig pwm4Cfg {
	5120000,
	256,                                  /* Initial PWM period 1S.         */
	NULL,                                     /* Period callback.               */
	{
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},          		/* CH1 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH2 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL},             /* CH3 mode and callback.         */
	{PWM_OUTPUT_ACTIVE_HIGH, NULL}              /* CH4 mode and callback.         */
	},
	0,                                        /* Control Register 2.            */
	0                                         /* DMA/Interrupt Enable Register. */
};




// BoardDef kBoardDef {
// 	&PWMD4,
// 	0,
// 	&pwm4Cfg,
// 	GPIOD,
// 	12
// };


BoardDef kBoardDef {
	// motor 1A
	&PWMD4,
	0,
	&pwm4Cfg,
	GPIOD,
	12,
	2,

	// motor 1B
	&PWMD4,
	1,
	&pwm4Cfg,
	GPIOD,
	13,
	2,

	// LED 1
	&PWMD3,
	0,
	&pwm3Cfg,
	GPIOC,
	6,
	2,
	
	// LED 2
	&PWMD3,
	1,
	&pwm3Cfg,
	GPIOC,
	7,
	2,
	
	// LED 3
	&PWMD4,
	3,
	&pwm4Cfg,
	GPIOB,
	9,
	2,

	// Buzzer
	&PWMD1,
	3,
	&pwm1Cfg,
	GPIOE,
	14,
	1
};
