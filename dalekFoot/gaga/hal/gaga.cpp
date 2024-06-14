#include "gaga.h"

// Test code
#include <cstdint>
#include <cstring>
#include "stm32f4xx_hal.h"

// Test code end

namespace cooboc {
namespace hal {

std::uint8_t txData[1024];

Gaga::Gaga(UART_HandleTypeDef *huart1) : huart1_ {huart1} {}

void Gaga::setup() { memset(txData, 'a', 1024); }
void Gaga::tick() {
    HAL_UART_Transmit(huart1_, txData, 1024, 1000);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(500);
}
}    // namespace hal
}    // namespace cooboc
