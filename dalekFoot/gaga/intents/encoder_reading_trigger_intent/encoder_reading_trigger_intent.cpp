#include "intents/encoder_reading_trigger_intent/encoder_reading_trigger_intent.h"
#include "hal/hal.h"
#include "stm32f4xx_hal.h"

namespace cooboc {
namespace intents {
EncoderReadingTriggerIntent::EncoderReadingTriggerIntent() {}
void EncoderReadingTriggerIntent::setup() {}
void EncoderReadingTriggerIntent::tick() {
    hal::gagaEncoder.beginReading();
    // setup clock pin
    // GPIO_InitTypeDef GPIO_InitStruct = {0};


    // // Setup SDA pin
    // GPIO_InitStruct.Pin   = GPIO_PIN_5;
    // GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    // GPIO_InitStruct.Pull  = GPIO_PULLUP;    // use external pull-up resister
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);


    // HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
}
}    // namespace intents
}    // namespace cooboc