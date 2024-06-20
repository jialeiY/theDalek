#include "hal/motor.h"
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
 * PWM1.B   D13
 * PWM2.A   D14
 * PWM2.B   D15
 * PWM3.A   C8
 * PWM3.B   A15
 *
 */

Motor::Motor() {}
void Motor::setup() {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 10240);
}
void Motor::tick() {}

void Motor::setPower(std::int16_t value) {
    if (value > 0) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
        // __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, value);
    } else {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);

        // __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1024);
    }
}

Motor motor;

}    // namespace hal
}    // namespace cooboc