#include "gaga.h"
#include <cstdint>
#include <cstring>
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"

// Test code end

char txData[1024];
bool isSent {true};
char c {'a'};

constexpr std::size_t SPI_LENGTH {4U};

std::uint8_t spiTxBuffer[100] {0x10, 0x20, 0x30};
std::uint8_t spiRxBuffer[100] {0};

#ifdef __cplusplus
extern "C" {
#endif
extern SPI_HandleTypeDef hspi2;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    // isSent = true;
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);

    char txData[1024];
    int len = sprintf(txData,
                      "SPI: %x %x %x %x  %x %x %x %x\r\n",
                      spiRxBuffer[0],
                      spiRxBuffer[1],
                      spiRxBuffer[2],
                      spiRxBuffer[3],
                      spiRxBuffer[4],
                      spiRxBuffer[5],
                      spiRxBuffer[6],
                      spiRxBuffer[7]);
    HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)txData, len);

    HAL_SPI_TransmitReceive_DMA(&hspi2, spiTxBuffer, spiRxBuffer, 4);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)"rx\r\n", 4);
    HAL_SPI_Receive_DMA(&hspi2, spiRxBuffer, 1);
}

#ifdef __cplusplus
}
#endif
namespace cooboc {
namespace hal {


Gaga::Gaga() {}

void Gaga::setup() {
    HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)"begin\r\n", 7);
    c = 'a';
    memset(txData, c, 1024);
    txData[1023] = '0';
    isSent       = true;

    HAL_SPI_TransmitReceive_DMA(&hspi2, spiTxBuffer, spiRxBuffer, 3);
    // HAL_SPI_Receive_DMA(&hspi2, spiRxBuffer, 1);
}

// For printf library
void _putchar(char character) {}


void Gaga::tick() {
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
    int len = sprintf(txData, "hello world  %u\r\n", HAL_GetTick());
    // HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)txData, len);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(500);
}

}    // namespace hal
}    // namespace cooboc
