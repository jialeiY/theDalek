#include "hal/motor.h"
#include <array>
#include "hal/board_def.h"
#include "stm32f4xx_hal.h"

namespace cooboc {
namespace hal {


/**
 * A1.1 D0
 * A1.2 D1
 * B1.1 D2
 * B1.2 D3
 * A2.1 D4
 * A2.2 D5
 * B2.1 D6
 * B2.2 D7
 * A3.1 D8
 * A3.2 D9
 * B3.1 D10
 * B3.2 D11
 * PWM1.A   D12 TIM4_CH1
 * PWM1.B   D13 TIM4_CH2
 * PWM2.A   D14 TIM4_CH3
 * PWM2.B   D15 TIM4_CH4
 * PWM3.A   C8  TIM3_CH3
 * PWM3.B   A15 TIM2_CH1
 *
 */

Motor::Motor(GPIO_TypeDef* portA,
             const std::uint16_t pinA,
             GPIO_TypeDef* portB,
             const std::uint16_t pinB,
             TIM_HandleTypeDef* pwmTimer,
             const uint32_t pwmChannel) :
    portA_ {portA},
    pinA_ {pinA},
    portB_ {portB},
    pinB_ {pinB},
    pwmTimer_ {pwmTimer},
    pwmChannel_ {pwmChannel} {}

void Motor::setup() const {
    HAL_GPIO_WritePin(portA_, pinA_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(portB_, pinB_, GPIO_PIN_RESET);
    HAL_TIM_PWM_Start(pwmTimer_, pwmChannel_);
    __HAL_TIM_SET_COMPARE(pwmTimer_, pwmChannel_, 0);
}
void Motor::tick() {}

void Motor::setPower(std::int16_t value) {
    if (value > 0) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, value);
    } else {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, -value);
    }
}

std::array<Motor, 6U> gagaMotors {
  Motor {GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1, &htim4, TIM_CHANNEL_1},
  Motor {GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3, &htim4, TIM_CHANNEL_2},
  Motor {GPIOD, GPIO_PIN_4, GPIOD, GPIO_PIN_5, &htim4, TIM_CHANNEL_3},
  Motor {GPIOD, GPIO_PIN_6, GPIOD, GPIO_PIN_7, &htim4, TIM_CHANNEL_4},
  Motor {GPIOD, GPIO_PIN_8, GPIOD, GPIO_PIN_9, &htim3, TIM_CHANNEL_3},
  Motor {GPIOD, GPIO_PIN_10, GPIOD, GPIO_PIN_11, &htim2, TIM_CHANNEL_1},

};

}    // namespace hal
}    // namespace cooboc