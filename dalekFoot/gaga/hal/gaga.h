#ifndef __HAL_GAGA_H__
#define __HAL_GAGA_H__

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif


extern UART_HandleTypeDef huart1;
namespace cooboc {
namespace hal {


class Gaga {
  public:
    Gaga();
    void setup();
    void tick();

  private:
};
}    // namespace hal
}    // namespace cooboc

#endif
