#ifndef __HAL_GAGA_H__
#define __HAL_GAGA_H__

#include "spi.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif


namespace cooboc {
namespace hal {


class Gaga {
  public:
    Gaga();
    void setup();
    void tick();

  private:
    void onSpiDataReceived(const SpiProtocol &spi);

    void speedControlTest();
    void i2cfrequencyTest();
    void initTimer5(const std::uint32_t pre, const std::uint32_t period);
    void statisticizeI2cReading(const std::uint32_t pre,
                                const std::uint32_t period);
};
}    // namespace hal
}    // namespace cooboc

#endif
