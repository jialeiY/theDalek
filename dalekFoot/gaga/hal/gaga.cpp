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
    HAL_Delay(50);


    // // Setup the encoder
    // constexpr std::uint8_t devAddr {0x36};
    // constexpr std::uint8_t confRegAddr {0x07};
    // constexpr std::uint8_t statusRegAddr {0x0B};

    // // Read Configuration
    // gagaI2C.read(devAddr, confRegAddr, 2U);
    // while (gagaI2C.isBusy());    // Wait for finish

    // std::uint8_t *data = gagaI2C.__getData();

    // char b1[9];
    // char b2[9];

    // gagaSerial.println("conf: %s %s",
    //                    math::printBits(data[0], b1),
    //                    math::printBits(data[1], b2));
    // HAL_Delay(50);

    // // Read Status
    // gagaI2C.read(devAddr, statusRegAddr, 1U);
    // while (gagaI2C.isBusy());    // Wait for finish

    // data = gagaI2C.__getData();

    // gagaSerial.println("status: %s", math::printBits(data[0], b1));
    // HAL_Delay(50);
}


void Gaga::tick() {
    // static std::uint16_t lastRead {0U};
    // gagaI2C.read(0x36, 0x0B, 3U);
    // HAL_Delay(1);
    // while (gagaI2C.isBusy());    // Wait until release
    // std::uint8_t *data  = gagaI2C.__getData();
    // const uint8_t hb    = data[1];
    // const uint8_t lb    = data[2];
    // const uint8_t sb    = data[0];
    // std::uint16_t value = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;

    // std::int32_t speed = value - lastRead;
    // if (speed > 2048)
    //     speed -= 4096;
    // if (speed < -2048)
    //     speed += 4096;
    // lastRead = value;

    // char str[9];
    // // gagaSerial.println(
    // // "value: %d %d %s", speed, value, math::printBits(sb, str));
    // gagaSerial.println("%d,%d", value, speed);


    // gagaI2C.write(0x36, 0x00, nullptr, 0U);
    // while (gagaI2C.isBusy());
    // gagaSerial.println("done");

    // HAL_Delay(1);

    speedControlTest();
}

void Gaga::speedControlTest() {
    // Read the value of encoder
    gagaI2C.read(0x36, 0x0E, 2U);
    while (gagaI2C.isBusy());    // Wait for encode read finished
    std::uint8_t *data    = gagaI2C.__getData();
    const std::uint8_t hb = data[0];
    const std::uint8_t lb = data[1];
    std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;

    // Calculate speed of motor
    static std::uint16_t lastRead {0U};
    std::int32_t speed = value - lastRead;
    lastRead           = value;
    if (speed > 2048)
        speed -= 4096;
    if (speed < -2048)
        speed += 4096;
    speed = -speed;

    // Control the motor
    static float integralError {0.0F};
    constexpr float targetSpeed         = 25.0f;
    constexpr float nominalControlValue = 1024;
    constexpr float kp                  = 100.0f;
    constexpr float ki                  = 0.05F;

    const float errorSpeed = static_cast<float>(speed) - targetSpeed;
    integralError += errorSpeed;

    float controlValue =
      nominalControlValue - kp * errorSpeed - ki * integralError;

    // TODO: clamp to value range of int16

    // gagaMotors[0].setPower(static_cast<std::int16_t>(controlValue));

    gagaMotors[0].setPower(
      static_cast<std::int16_t>(math::clamp(controlValue, -2048.0F, 2048.0F)));
    // gagaMotors[0].setPower(1000);


    HAL_Delay(1);
    gagaSerial.println("%f, %d, %f", controlValue, speed, errorSpeed);
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
