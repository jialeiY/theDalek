#include "hal/serial.h"
#include <cstdarg>
#include <cstdint>
#include "hal/board_def.h"
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

GagaSerial::GagaSerial() {}
void GagaSerial::setup() {}
void GagaSerial::tick() {}
int GagaSerial::println(const char *format, ...) {
    char buffer[512];
    va_list va;
    va_start(va, format);
    int len = vsnprintf(buffer, 510, format, va);
    va_end(va);
    buffer[len]     = '\r';
    buffer[len + 1] = '\n';
    len += 2;
    HAL_UART_Transmit_DMA(&huart1, (const std::uint8_t *)(buffer), len);
    return len;
}

GagaSerial gagaSerial;

}    // namespace hal
}    // namespace cooboc