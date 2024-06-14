#ifndef __HAL_GAGA_H__
#define __HAL_GAGA_H__

#include "stm32f4xx_hal.h"

namespace cooboc {
namespace hal {
class Gaga {
  public:
    Gaga(UART_HandleTypeDef *huart1);
    void setup();
    void tick();

  private:
    UART_HandleTypeDef *huart1_;
};
}    // namespace hal
}    // namespace cooboc

#endif
