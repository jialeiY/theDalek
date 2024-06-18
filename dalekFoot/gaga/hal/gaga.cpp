#include "gaga.h"
#include <cstdint>
#include "hal/board_def.h"
#include "hal/spi.h"
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"


#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    // isSent = true;
}


#ifdef __cplusplus
}
#endif


namespace cooboc {
namespace hal {


Gaga::Gaga() {}

void Gaga::setup() {
    gagaSpi.setup([this](const SpiProtocol &spi) { onSpiDataReceived(spi); });
    HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)"begin\r\n", 7);


    gagaSpi.begin();
}


void Gaga::tick() {
    // HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)txData, len);

    // if (isSent) {
    //     // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    //     c++;
    //     if (c > 'z') {
    //         c = 'a';
    //     }
    //     memset(txData, c, 1024);
    //     txData[1023] = '/';
    //     // HAL_UART_Transmit_DMA(huart1_, txData, 1024);
    //     printf("hello ");

    //     // HAL_UART_DMAResume(huart1_);
    //     isSent = false;
    // }

    // printf("hello ");
    // double f = 2.31323;
    // int len = sprintf(txData, "hello world  %u\r\n", HAL_GetTick());
    // HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)txData, len);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(500);
}

void Gaga::onSpiDataReceived(const SpiProtocol &spi) {
    char buffer[512];
    int len = sprintf(buffer,
                      "SPI: %x %x %x %x\r\n",
                      spi.motorPower[0],
                      spi.motorPower[1],
                      spi.motorPower[2],
                      spi.motorPower[3]);
    HAL_UART_Transmit_DMA(&huart1, (const std::uint8_t *)(buffer), len);
}


Gaga gaga;

}    // namespace hal
}    // namespace cooboc
