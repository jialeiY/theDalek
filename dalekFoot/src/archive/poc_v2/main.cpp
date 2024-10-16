/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.hpp"
#include "hal.h"
#include "rt_test_root.h"
// #include "oslib_test_root.h"
#include "chprintf.h"
#include "driver/tb6612fng.h"
#include "hw/board_def.h"
#include "hw/pwm_controller.h"
#include "hal/led.h"
#include "hal/buzzer.h"

PwmController pwmM1a(
	kBoardDef.motor1APwmDriver,
	kBoardDef.motor1APwmChannel,
	kBoardDef.motor1APwmConf,
	kBoardDef.motor1APort,
	kBoardDef.motor1APad,
	kBoardDef.motor1AAFn
);

PwmController pwmM1b(
	kBoardDef.motor1BPwmDriver,
	kBoardDef.motor1BPwmChannel,
	kBoardDef.motor1BPwmConf,
	kBoardDef.motor1BPort,
	kBoardDef.motor1BPad,
	kBoardDef.motor1BAFn
);

PwmController pwmLed1(
	kBoardDef.led1PwmDriver,
	kBoardDef.led1PwmChannel,
	kBoardDef.led1PwmConf,
	kBoardDef.led1Port,
	kBoardDef.led1Pad,
	kBoardDef.led1AFn
);

PwmController pwmLed2(
	kBoardDef.led2PwmDriver,
	kBoardDef.led2PwmChannel,
	kBoardDef.led2PwmConf,
	kBoardDef.led2Port,
	kBoardDef.led2Pad,
	kBoardDef.led2AFn
);

PwmController pwmLed3(
	kBoardDef.led3PwmDriver,
	kBoardDef.led3PwmChannel,
	kBoardDef.led3PwmConf,
	kBoardDef.led3Port,
	kBoardDef.led3Pad,
	kBoardDef.led3AFn
);

PwmController pwmBuzzer(
	kBoardDef.buzzerPwmDriver,
	kBoardDef.buzzerPwmChannel,
	kBoardDef.buzzerPwmConf,
	kBoardDef.buzzerPort,
	kBoardDef.buzzerPad,
	kBoardDef.buzzerAFn
);



Tb6612fng tb6612(
	GPIOD, 0,
	GPIOD, 1,
	GPIOD, 2,
	GPIOD, 3,
	pwmM1a,
	pwmM1b);

Led led1(pwmLed1);
Led led2(pwmLed2);
Led led3(pwmLed3);
Buzzer buzzer(pwmBuzzer);


using namespace chibios_rt;

/*
 * LED blink sequences.
 * NOTE: Sequences must always be terminated by a GOTO instruction.
 * NOTE: The sequencer language could be easily improved but this is outside
 *       the scope of this demo.
 */
#define SLEEP 0
#define GOTO 1
#define STOP 2
#define BITCLEAR 3
#define BITSET 4

typedef struct
{
	uint8_t action;
	uint32_t value;
} seqop_t;

// Flashing sequence for LED3.
static const seqop_t LED3_sequence[] =
		{
				{BITSET, PAL_PORT_BIT(GPIOD_LED3)},
				{SLEEP, 800},
				{BITCLEAR, PAL_PORT_BIT(GPIOD_LED3)},
				{SLEEP, 200},
				{GOTO, 0}};

// Flashing sequence for LED4.
static const seqop_t LED4_sequence[] =
		{
				{BITSET, PAL_PORT_BIT(GPIOD_LED4)},
				{SLEEP, 600},
				{BITCLEAR, PAL_PORT_BIT(GPIOD_LED4)},
				{SLEEP, 400},
				{GOTO, 0}};

// Flashing sequence for LED5.
static const seqop_t LED5_sequence[] =
		{
				{BITSET, PAL_PORT_BIT(GPIOD_LED5)},
				{SLEEP, 400},
				{BITCLEAR, PAL_PORT_BIT(GPIOD_LED5)},
				{SLEEP, 600},
				{GOTO, 0}};

// Flashing sequence for LED6.
static const seqop_t LED6_sequence[] =
		{
				{BITSET, PAL_PORT_BIT(GPIOD_LED6)},
				{SLEEP, 200},
				{BITCLEAR, PAL_PORT_BIT(GPIOD_LED6)},
				{SLEEP, 800},
				{GOTO, 0}};

/*
 * Sequencer thread class. It can drive LEDs or other output pins.
 * Any sequencer is just an instance of this class, all the details are
 * totally encapsulated and hidden to the application level.
 */
class SequencerThread : public BaseStaticThread<128>
{
private:
	const seqop_t *base, *curr; // Thread local variables.

protected:
	virtual void main(void)
	{

		setName("sequencer");

		while (true)
		{
			switch (curr->action)
			{
			case SLEEP:
				sleep(TIME_MS2I(curr->value));
				break;
			case GOTO:
				curr = &base[curr->value];
				continue;
			case STOP:
				return;
			case BITCLEAR:
				palClearPort(GPIOD, curr->value);
				break;
			case BITSET:
				palSetPort(GPIOD, curr->value);
				break;
			}
			curr++;
		}
	}

public:
	SequencerThread(const seqop_t *sequence) : BaseStaticThread<128>()
	{

		base = curr = sequence;
	}
};

/*
 * Tester thread class. This thread executes the test suite.
 */
// class TesterThread : public BaseStaticThread<256>
// {

// protected:
// 	virtual void main(void)
// 	{

// 		setName("tester");

// 		test_execute((BaseSequentialStream *)&SD2, &rt_test_suite);
// 		test_execute((BaseSequentialStream *)&SD2, &oslib_test_suite);
// 		exit(test_global_fail);
// 	}

// public:
// 	TesterThread(void) : BaseStaticThread<256>()
// 	{
// 	}
// };

/* Static threads instances.*/
// static TesterThread tester;
// static SequencerThread blinker1(LED3_sequence);
// static SequencerThread blinker2(LED4_sequence);
// static SequencerThread blinker3(LED5_sequence);
// static SequencerThread blinker4(LED6_sequence);

/*
 * Application entry point.
 */

static const SerialConfig sdcfg = {
  115200,
  0,
  USART_CR2_STOP1_BITS,
	0
};

static BaseSequentialStream* chp = (BaseSequentialStream*) &SD1;


/*
static void extcb1(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;

}


static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, extcb1},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
  }
};
*/


static volatile uint8_t encoder4A = 0;
static volatile uint8_t encoder4B = 0;
static volatile uint32_t encoder4 = 0;

static event_source_t button_pressed_event;
static event_source_t button_released_event;

static void irqEncoderPort4A(void *) {
	System::lockFromIsr();
	encoder4A = palReadPad(GPIOC, 9);
	if (encoder4B) {
		encoder4 += static_cast<bool>(encoder4A) ? 1 : -1;
	} else {
		encoder4 += static_cast<bool>(encoder4A) ? -1 : 1;
	}
	encoder4++;
	System::unlockFromIsr();
}

static void irqEncoderPort4B(void *) {
	sdPut(&SD1, 'o');
	System::lockFromIsr();
	encoder4B = palReadPad(GPIOA, 8);
	if (encoder4A) {
		encoder4 += static_cast<bool>(encoder4B) ? -1 : 1;
	} else {
		encoder4 += static_cast<bool>(encoder4B) ? 1 : -1;
	}
	encoder4++;
	System::unlockFromIsr();
}


void ext() {
	// extInit();
	// extStart(&EXTD1, &extcfg);
	palSetPadMode(GPIOC, 9, PAL_MODE_INPUT);
	palSetPadMode(GPIOA, 8, PAL_MODE_INPUT);

  palEnableLineEvent(PAL_LINE(GPIOC, 9U), PAL_EVENT_MODE_BOTH_EDGES);
  palSetLineCallback(PAL_LINE(GPIOC, 9U), irqEncoderPort4A, nullptr);
	palEnableLineEvent(PAL_LINE(GPIOA, 8U), PAL_EVENT_MODE_BOTH_EDGES);
  palSetLineCallback(PAL_LINE(GPIOA, 8U), irqEncoderPort4B, nullptr);

}


int main(void) {
	event_listener_t el0, el1;
	halInit();
	System::init();
	tb6612.init();
	led1.init();
	led2.init();
	led3.init();
	buzzer.init();

	chEvtObjectInit(&button_pressed_event);
  chEvtObjectInit(&button_released_event);
  chEvtRegister(&button_pressed_event, &el0, 0);
  chEvtRegister(&button_released_event, &el1, 1);

	//ext();
	
	sdStart(&SD1, &sdcfg);
	
	palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));
	palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));
	
	// char buf[128];
	chprintf(chp, "size: %d\r\n", 5);
	// (&SD1, buf, sizeof(buf));
	

	int v = 0;
	tb6612.on();
	buzzer.tone(20000);
	buzzer.stop();
	tb6612.debug(20);
	// const unsigned char * data = static_cast<const unsigned char *>("hello world\r\n");
	while (true)
	{
		
		led1.setBrightness(v);
		led2.setBrightness(v);
		led3.setBrightness((256-v) % 256);
		//buzzer.tone(20000 + v * 100);
		v += 4;
		if (v >= 255) v = 0;
		BaseThread::sleep(TIME_MS2I(200));
		// sdWrite(&SD1, (const uint8_t *)"hello gelaoshi\r\n", 16);
		// chprintf(chp, "size: %d\r\n", 5);
		
		chprintf(chp, "enc: %lu\r\n", encoder4);
	}

	return 0;
}
