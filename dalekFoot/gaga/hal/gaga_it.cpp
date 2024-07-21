#include "hal/gaga_it.h"
#include "hal/driver/i2c.h"
#include "hal/gaga.h"


namespace cooboc {
namespace hal {
extern cooboc::hal::Gaga gaga;
}
}    // namespace cooboc
#ifdef __cplusplus
extern "C" {
#endif

// Inject the timer interrupt
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim5) {
        // I2C
        cooboc::hal::gagaI2C.__IT_onCapture();
    }
    if (htim == &htim9) {
        // main cycle
        cooboc::hal::gaga.__IT_onTimeout();
    }
}
// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) { LED2_TOGGLE; }
#ifdef __cplusplus
}
#endif