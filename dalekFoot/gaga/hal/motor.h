#ifndef __HAL_MOTOR_H__
#define __HAL_MOTOR_H__

#include <array>
#include <cstdint>
#include "hal/board_def.h"

namespace cooboc {
namespace hal {

class Motor {
  public:
    Motor() = default;
    void setup(GPIO_TypeDef* portA,
               std::uint16_t pinA,
               GPIO_TypeDef* portB,
               const std::uint16_t pinB,
               TIM_HandleTypeDef* pwmTimer,
               const uint32_t pwmChannel);
    void setPower(std::int16_t value);

  private:
    GPIO_TypeDef* portA_;
    std::uint16_t pinA_;
    GPIO_TypeDef* portB_;
    std::uint16_t pinB_;
    TIM_HandleTypeDef* pwmTimer_;
    uint32_t pwmChannel_;
};


extern std::array<Motor, 6U> gagaMotors;
}    // namespace hal
}    // namespace cooboc
#endif
