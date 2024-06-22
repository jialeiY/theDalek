#ifndef __HAL_MOTOR_H__
#define __HAL_MOTOR_H__

#include <array>
#include <cstdint>
#include "hal/board_def.h"

namespace cooboc {
namespace hal {

class Motor {
  public:
    explicit Motor(GPIO_TypeDef* portA,
                   const std::uint16_t pinA,
                   GPIO_TypeDef* portB,
                   const std::uint16_t pinB,
                   TIM_HandleTypeDef* pwmTimer,
                   const uint32_t pwmChannel);
    void setup() const;
    void tick();
    void setPower(std::int16_t value);

  private:
    mutable GPIO_TypeDef* portA_;
    const std::uint16_t pinA_;
    mutable GPIO_TypeDef* portB_;
    const std::uint16_t pinB_;
    mutable TIM_HandleTypeDef* pwmTimer_;
    const uint32_t pwmChannel_;
};


extern std::array<Motor, 6U> gagaMotors;
}    // namespace hal
}    // namespace cooboc
#endif
