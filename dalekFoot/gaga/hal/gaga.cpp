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
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    isSent = true;
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
    if (isSent) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        c++;
        if (c > 'z') {
            c = 'a';
        }
        memset(txData, c, 1024);
        txData[1023] = '/';
        HAL_UART_Transmit_DMA(huart1_, txData, 1024);

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
