#include "gaga.h"
#include <cstdint>
#include <limits>
#include "hal/board_def.h"
#include "hal/motor.h"
#include "hal/serial.h"
#include "hal/spi.h"
#include "intents/common/intent_manager.h"
#include "math/utils.h"
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"

namespace cooboc {
namespace hal {


Gaga::Gaga() {}

void Gaga::setup() {
    motor.setup();
    gagaSerial.setup();
    gagaSpi.setup([this](const SpiProtocol &spi) { onSpiDataReceived(spi); });
    intents::intentManager.setup();


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

    // gagaSerial.println("SPI: %x %x %x %x",
    //                    spi.motorPower[0],
    //                    spi.motorPower[1],
    //                    spi.motorPower[2],
    //                    spi.motorPower[3]);

    intents::intentManager.launch();
    std::int32_t motorPower =
      math::lerp(spi.motorPower[0],
                 std::numeric_limits<std::int8_t>::min(),
                 std::numeric_limits<std::int8_t>::max(),
                 -2048,
                 2048);
    // motor.setPower(motorPower);
    // motor.setPower(-1500);
    gagaSerial.println("motor power: %d", motorPower);

    // Turn the led on
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}


Gaga gaga;

}    // namespace hal
}    // namespace cooboc
