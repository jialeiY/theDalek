#include "hal/i2c.h"
#include "hal/board_def.h"

#ifdef __cplusplus
extern "C" {
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim5) {
        cooboc::hal::gagaI2c.__onCapture();
    }
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    // LED2_TOGGLE;
}
#ifdef __cplusplus
}
#endif

namespace cooboc {
namespace hal {

void I2C::setup() {
    isWorknig_ = false;

    // setup clock pin: PE8
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin              = GPIO_PIN_8;
    GPIO_InitStruct.Mode             = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull             = GPIO_NOPULL;
    GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);


    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim5);
}
void I2C::tick() {}

void I2C::__onCapture() {
    //
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    //
    HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
}

I2C gagaI2c;

}    // namespace hal
}    // namespace cooboc
// HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);