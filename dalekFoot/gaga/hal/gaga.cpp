#include "gaga.h"
#include <cstdio>
// Test code
#include <cstdint>
#include <cstring>
#include "stm32f4xx_hal.h"

// Test code end


namespace cooboc {
namespace hal {

std::uint8_t txData[1024];
bool isSent {true};
char c {'a'};

#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_UART_DMAStop(huart);
    isSent = true;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}

#ifdef __cplusplus
}
#endif

Gaga::Gaga(UART_HandleTypeDef *huart1) : huart1_ {huart1} {}

void Gaga::setup() {
    c = 'a';
    memset(txData, c, 1024);
    txData[1023] = '0';
    isSent       = true;
}

void Gaga::tick() {
    // Sychronized
    // HAL_UART_Transmit(huart1_, txData, 1024, 1000);

    // Interrupted
    if (isSent) {
        c++;
        if (c > 'z') {
            c = 'a';
        }
        memset(txData, c, 1024);
        txData[1023] = '0';
        HAL_UART_Transmit_IT(huart1_, txData, 1024);

        // HAL_UART_DMAResume(huart1_);
        isSent = false;
    }


    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

    HAL_Delay(500);
}
}    // namespace hal
}    // namespace cooboc
