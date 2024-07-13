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
    // HAL_Delay(5000);

    // // Read Status
    // gagaI2C.read(devAddr, statusRegAddr, 1U);
    // while (gagaI2C.isBusy());    // Wait for finish

    // data = gagaI2C.__getData();

    // gagaSerial.println("status: %s", math::printBits(data[0], b1));
    // HAL_Delay(50);
    encoderConfReadTest();
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
    // gagaMotors[0].setPower(400);
    // char str[9];
    // // gagaSerial.println("%d\t%d\t%s%s%s",
    // //                    speed,
    // //                    value,
    // //                    sb & 0x20 ? "4" : "",
    // //                    sb & 0x10 ? "2" : "",
    // //                    sb & 0x80 ? "0" : "");
    // // gagaSerial.println("%d,%d", value, speed);
    // gagaSerial.println("%f", static_cast<float>(value));

    // HAL_Delay(1);

    // speedControlTest();
    // i2cfrequencyTest();
    // calibrationMotorSpeed();
    encoderReadTest();
}

void Gaga::speedControlTest() {
    HAL_Delay(1);
    // std::int32_t speed = readSpeedTest();
    gagaI2C.read(0x36, 0x0E, 2U);
    while (gagaI2C.isBusy());    // Wait for encode read finished

    std::uint8_t *data    = gagaI2C.__getData();
    const std::uint8_t hb = data[0];
    const std::uint8_t lb = data[1];
    std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;


    // Control the motor
    static float integralError {0.0F};
    constexpr float targetSpeed         = 25.0F;
    constexpr float nominalControlValue = 36.27 * targetSpeed + 110.65;
    constexpr float kp                  = 100.0f;
    constexpr float ki                  = 0.05F;

    // const float errorSpeed = static_cast<float>(speed) - targetSpeed;
    // integralError += errorSpeed;

    float controlValue =
      nominalControlValue;    //-kp * errorSpeed - ki * integralError;

    // TODO: clamp to value range of int16

    // gagaMotors[0].setPower(static_cast<std::int16_t>(controlValue));

    gagaMotors[0].setPower(
      static_cast<std::int16_t>(math::clamp(controlValue, -2048.0F, 2048.0F)));
    // gagaMotors[0].setPower(1000);


    gagaSerial.println("%f", static_cast<float>(value));


    // HAL_Delay(0);
}

void Gaga::i2cfrequencyTest() {
    for (std::uint32_t pre {7U}; pre < 100U; ++pre) {
        for (std::uint32_t period {20U}; period < 200U; period += 5U) {
            initTimer5(pre, period);
            statisticizeI2cReading(pre, period);
        }
    }
    while (true);
}


void Gaga::initTimer5(const std::uint32_t pre, const std::uint32_t period) {
    __HAL_TIM_SET_PRESCALER(&htim5, pre);
    __HAL_TIM_SET_AUTORELOAD(&htim5, period);
}

void Gaga::statisticizeI2cReading(const std::uint32_t pre,
                                  const std::uint32_t period) {
    constexpr std::size_t kCount {10U};
    std::uint32_t totalTime {0U};
    for (std::size_t i {0U}; i < kCount; ++i) {
        HAL_Delay(2);
        std::uint32_t startTick = uwTick;
        std::uint32_t startTime = SysTick->VAL;
        gagaI2C.read(0x36, 0x0E, 2U);
        while (gagaI2C.isBusy());    // Wait for encode read finished


        std::uint32_t endTime = SysTick->VAL;
        std::uint32_t endTick = uwTick;

        std::uint32_t thistime =
          (endTick - startTick) * 180000U + startTime - endTime;
        totalTime += (thistime);
    }
    gagaSerial.println("%d, %d, %d", pre, period, totalTime);
}


void Gaga::calibrationMotorSpeed() {
    // Init
    readSpeedTest();

    for (int power {100}; power < 2100; power += 100) {
        // Step 1. setup a power
        gagaMotors[0].setPower(power);
        // Wait 1 second for stable output;
        HAL_Delay(1000);
        // Read Speed
        std::uint32_t startMillis = HAL_GetTick();
        std::int64_t odometry {0};
        std::int32_t speed;
        while ((HAL_GetTick() - startMillis) < 3000U) {
            HAL_Delay(1);
            speed = readSpeedTest();
            odometry += speed;
        }
        gagaSerial.println("%d, %d, %d", power, odometry, speed);
    }
    gagaMotors[0].setPower(0);
    while (true);
}


std::int32_t Gaga::readSpeedTest() {
    static std::int32_t lastRead {0};

    gagaI2C.read(0x36, 0x0E, 2U);
    while (gagaI2C.isBusy());    // Wait for encode read finished

    std::uint8_t *data    = gagaI2C.__getData();
    const std::uint8_t hb = data[0];
    const std::uint8_t lb = data[1];
    std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;

    std::int32_t speed = value - lastRead;
    lastRead           = value;

    if (speed > 2048) {
        speed -= 4096;
    }
    if (speed < -2048) {
        speed += 4096;
    }

    return -speed;
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

void Gaga::encoderConfReadTest() {
    // Setup the encoder
    constexpr std::uint8_t devAddr {0x36};
    constexpr std::uint8_t confRegAddr {0x07};

    // Read Configuration
    gagaI2C.read(devAddr, confRegAddr, 2U);
    while (gagaI2C.isBusy());    // Wait for finish
    std::uint8_t *data = gagaI2C.__getData();

    char b1[9];
    char b2[9];

    gagaSerial.println("conf: %s %s",
                       math::printBits(data[0], b1),
                       math::printBits(data[1], b2));

    HAL_Delay(200);

    constexpr std::uint8_t updatedConf[2] {0x03, 0x00};

    gagaI2C.write(devAddr, confRegAddr, updatedConf, 2U);
    HAL_Delay(1);
    while (gagaI2C.isBusy());    // wait for waitting
    HAL_Delay(5);                // wait for making effecting

    // Lets read again
    gagaI2C.read(devAddr, confRegAddr, 2U);
    while (gagaI2C.isBusy());    // Wait for finish
    data = gagaI2C.__getData();
    gagaSerial.println("conf: %s %s",
                       math::printBits(data[0], b1),
                       math::printBits(data[1], b2));
}


void Gaga::encoderReadTest() {
    HAL_Delay(1);    // align timing
    gagaI2C.read(0x36, 0x0E, 2U);
    while (gagaI2C.isBusy());
    std::uint8_t *data    = gagaI2C.__getData();
    const std::uint8_t hb = data[0];
    const std::uint8_t lb = data[1];
    std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;
    HAL_Delay(1);
    gagaI2C.read(0x36, 0x1A, 1U);
    while (gagaI2C.isBusy());
    data    = gagaI2C.__getData();
    int agc = data[0];

    gagaSerial.println("%d, %d", (int)(value), (int)agc);

    HAL_Delay(10);
}

Gaga gaga;

}    // namespace hal
}    // namespace cooboc
