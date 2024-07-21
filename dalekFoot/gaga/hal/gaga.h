#ifndef __HAL_GAGA_H__
#define __HAL_GAGA_H__

#include "spi.h"
#include "stm32f4xx_hal.h"


namespace cooboc {
namespace hal {


class Gaga {
  public:
    Gaga() = default;
    void setup();
    void begin();
    inline void tick();

    void __IT_onTimeout();

  private:
    struct Odometry {
        std::uint16_t encoder {0U};
        std::int32_t speed {0};
    };
    void onSpiDataReceived(const SpiProtocol &spi);

    // void speedControlTest();
    // void calibrationMotorSpeed();
    // inline Odometry readSpeedTest();
    // inline void encoderConfReadTest();
    // inline void encoderReadTest();
    std::int16_t testSpeed_ {0};
};

}    // namespace hal
}    // namespace cooboc

#endif
