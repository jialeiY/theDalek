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
    struct Odometry {
        std::uint16_t encoder {0U};
        std::int32_t speed {0};
    };
    void onSpiDataReceived(const SpiProtocol &spi);

    void speedControlTest();
    void i2cfrequencyTest();
    void initTimer5(const std::uint32_t pre, const std::uint32_t period);
    void statisticizeI2cReading(const std::uint32_t pre,
                                const std::uint32_t period);
    void calibrationMotorSpeed();
    inline Odometry readSpeedTest();
    inline void encoderConfReadTest();
    inline void encoderReadTest();
    std::int16_t testSpeed_ {0};
};

}    // namespace hal
}    // namespace cooboc

#endif
