#include "gaga.h"
#include <cstdint>
#include <cstring>
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"

// Test code end


namespace cooboc {
namespace hal {

char txData[1024];
bool isSent {true};
char c {'a'};


#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
    isSent = true;
}


#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
extern UART_HandleTypeDef huart1;
PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    return ch;
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
    double f = 2.31323;
    int len  = sprintf(txData, "hello world  %u\r\n", HAL_GetTick());
    HAL_UART_Transmit_DMA(huart1_, (std::uint8_t *)txData, len);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);

    HAL_Delay(500);
}
}    // namespace hal
}    // namespace cooboc
