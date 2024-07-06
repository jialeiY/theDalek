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
    //
    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_UPDATE);


    HAL_TIM_Base_Start_IT(&htim5);
}
void I2C::tick() {}
void I2C::__onCapture() {
    //
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    //
}

I2C gagaI2c;

}    // namespace hal
}    // namespace cooboc
// HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);