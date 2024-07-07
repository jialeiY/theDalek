#include "gaga.h"
#include <cstdint>
#include <limits>
#include "hal/board_def.h"
#include "hal/i2c.h"
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
    for (const Motor &motor : gagaMotors) { motor.setup(); }

    gagaSerial.setup();
    gagaSpi.setup([this](const SpiProtocol &spi) { onSpiDataReceived(spi); });
    gagaI2C.setup();

    intents::intentManager.setup();


    gagaSpi.begin();

    gagaSerial.println("begin");
}


void Gaga::tick() {
    // LED2_TOGGLE;
    // HAL_Delay(400);

    // LED1_ON;
    // HAL_Delay(50);
    // LED1_OFF;
    // HAL_Delay(50);
    gagaI2C.__testTrigger();
    HAL_Delay(50);
    LED1_ON;
    while (gagaI2C.isBusy());    // Wait until release
    LED1_OFF;
    const std::uint8_t *data = gagaI2C.__getData();
    std::uint16_t value =
      (static_cast<std::uint16_t>(data[0] & 0x0F) << 8U) | data[1];
    gagaSerial.println("value: %d", value);

    HAL_Delay(300);
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
    //  motor.setPower(-1500);
    gagaSerial.println("motor power: %d", motorPower);

    // Turn the led on
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}


Gaga gaga;

}    // namespace hal
}    // namespace cooboc
