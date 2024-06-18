#include "gaga.h"
#include <cstdint>
#include "hal/board_def.h"
#include "hal/motor.h"
#include "hal/serial.h"
#include "hal/spi.h"
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"

namespace cooboc {
namespace hal {


Gaga::Gaga() {}

void Gaga::setup() {
    gagaSerial.setup();
    gagaSpi.setup([this](const SpiProtocol &spi) { onSpiDataReceived(spi); });

    // HAL_UART_Transmit_DMA(&huart1, (std::uint8_t *)"begin\r\n", 7);


    gagaSpi.begin();

    gagaSerial.println("begin");
}


void Gaga::tick() {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(500);
}

void Gaga::onSpiDataReceived(const SpiProtocol &spi) {
    // Turn the led off
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);


    // char buffer[512];
    // int len = sprintf(buffer,
    //                   "SPI: %x %x %x %x\r\n",
    //                   spi.motorPower[0],
    //                   spi.motorPower[1],
    //                   spi.motorPower[2],
    //                   spi.motorPower[3]);
    // HAL_UART_Transmit_DMA(&huart1, (const std::uint8_t *)(buffer), len);
    gagaSerial.println("SPI: %x %x %x %x",
                       spi.motorPower[0],
                       spi.motorPower[1],
                       spi.motorPower[2],
                       spi.motorPower[3]);
    // Turn the led on
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}


Gaga gaga;

}    // namespace hal
}    // namespace cooboc
