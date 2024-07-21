#include "gaga.h"
#include <cmath>
#include <cstdint>
#include <limits>
#include "hal/board_def.h"
// #include "hal/driver/i2c.h"
#include "hal/encoder.h"
#include "hal/motor.h"
#include "hal/serial.h"
#include "hal/spi.h"
#include "intents/common/intent_manager.h"
#include "math/utils.h"
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"


namespace cooboc {
namespace hal {

void Gaga::setup() {
    // DEBUG
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode             = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pin              = GPIO_PIN_1;
        GPIO_InitStruct.Pull             = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
    // End of Debug

    // Init motors
    gagaMotors[0U].setup(
      GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1, &htim4, TIM_CHANNEL_1);
    gagaMotors[1U].setup(
      GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3, &htim4, TIM_CHANNEL_2);
    gagaMotors[2U].setup(
      GPIOD, GPIO_PIN_4, GPIOD, GPIO_PIN_5, &htim4, TIM_CHANNEL_3);
    gagaMotors[3U].setup(
      GPIOD, GPIO_PIN_6, GPIOD, GPIO_PIN_7, &htim4, TIM_CHANNEL_4);
    gagaMotors[4U].setup(
      GPIOD, GPIO_PIN_8, GPIOD, GPIO_PIN_9, &htim3, TIM_CHANNEL_3);
    gagaMotors[5U].setup(
      GPIOD, GPIO_PIN_10, GPIOD, GPIO_PIN_11, &htim2, TIM_CHANNEL_1);

    gagaSerial.setup();
    gagaSpi.setup([this](const SpiProtocol &spi) { onSpiDataReceived(spi); });
    gagaEncoder.setup();


    intents::intentManager.setup();


    gagaSerial.println("begin");
    HAL_Delay(50);


    // encoderConfReadTest();
    // Init speed register
    // readSpeedTest();


    // Set the PA0 to output, just for test
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin              = GPIO_PIN_0;
        GPIO_InitStruct.Mode             = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull             = GPIO_NOPULL;
        GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    }
}    // namespace hal

void Gaga::begin() {
    gagaEncoder.begin();
    gagaSpi.begin();
    // Start main cycle tick
    __HAL_TIM_ENABLE_IT(&htim9, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim9);
}

void Gaga::__IT_onTimeout() { tick(); }

void Gaga::tick() {
    intents::intentManager.tick();
    // speedControlTest();
    // i2cfrequencyTest();
    // calibrationMotorSpeed();
    // encoderReadTest();
}

// void Gaga::speedControlTest() {
//     Odometry odo       = readSpeedTest();
//     std::int32_t speed = odo.speed;


//     float targetSpeed = 0.0F;
//     {
//         // Generate dynamic target speed
//         // cycle = 4000 milli seconds
//         // amplifer = 10 -> 40
//         constexpr int cycle {500};
//         const float timeShift = static_cast<float>(HAL_GetTick() % cycle) *
//                                 2.0F * 3.1415926 / static_cast<float>(cycle);
//         targetSpeed =
//           math::lerp(std::sin(timeShift), -1.0F, 1.0F, 10.0F, 40.0F);
//     }
//     {
//         // Generate square wave
//         constexpr int cycle {1000};
//         const float timeShift = HAL_GetTick() % cycle;
//         targetSpeed           = timeShift < (cycle / 2) ? 10.0F : 40.0F;
//     }


//     targetSpeed = testSpeed_;

//     // Control the motor
//     static float integralError {0.0F};
//     // constexpr float targetSpeed         = 40.0F;
//     const float nominalControlValue = 28.27F * targetSpeed + 110.65;
//     // const float kp                  = 40.0f;
//     // const float ki                  = 0.1F;
//     const float kp = 80.0F;
//     const float ki = 3.50F;

//     const float errorSpeed = targetSpeed - static_cast<float>(speed);
//     integralError += errorSpeed;

//     static float lastControlValue {0.0F};
//     float controlValue =
//       nominalControlValue + kp * errorSpeed + ki * integralError;

//     // TODO: clamp to value range of int16

//     // gagaMotors[0].setPower(static_cast<std::int16_t>(controlValue));

//     // gagaMotors[0].setPower(
//     //   static_cast<std::int16_t>(math::clamp(controlValue, -2048.0F,
//     //   2048.0F)));

//     constexpr float maxControlChangingRate = 10000.0F;
//     const float clampedControlValue =
//       math::clamp(math::clamp(controlValue,
//                               lastControlValue - maxControlChangingRate,
//                               lastControlValue + maxControlChangingRate),
//                   -2048.0F,
//                   2048.0F);


//     gagaMotors[0].setPower(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1)
//                              ? clampedControlValue
//                              : nominalControlValue);
//     lastControlValue = clampedControlValue;

//     // gagaSerial.println("%d,%d,%d,%d",
//     //                    (int)targetSpeed,
//     //                    speed,
//     //                    (int)clampedControlValue,
//     //                    HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1));


//     gagaSerial.println("%d,%d", (int)odo.encoder, (int)odo.speed);


//     HAL_Delay(1);
// }


// void Gaga::calibrationMotorSpeed() {
//     // Init
//     readSpeedTest();

//     for (int power {100}; power < 2100; power += 100) {
//         // Step 1. setup a power
//         gagaMotors[0].setPower(power);
//         // Wait 1 second for stable output;
//         HAL_Delay(1000);
//         // Read Speed
//         std::uint32_t startMillis = HAL_GetTick();
//         std::int64_t odometry {0};
//         std::int32_t speed;
//         while ((HAL_GetTick() - startMillis) < 3000U) {
//             HAL_Delay(1);
//             speed = readSpeedTest().speed;
//             odometry += speed;
//         }
//         gagaSerial.println("%d, %d, %d", power, odometry, speed);
//     }
//     gagaMotors[0].setPower(0);
//     while (true);
// }


// Gaga::Odometry Gaga::readSpeedTest() {
//     static std::int32_t lastRead {0};
//     HAL_Delay(1);
//     gagaI2C.read(0x36, 0x0E, 2U);
//     while (gagaI2C.isBusy());    // Wait for encode read finished

//     std::uint8_t *data    = gagaI2C.__getData();
//     const std::uint8_t hb = data[0];
//     const std::uint8_t lb = data[1];
//     std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) |
//     lb;

//     std::int32_t speed = value - lastRead;
//     lastRead           = value;

//     if (speed > 2048) {
//         speed -= 4096;
//     }
//     if (speed < -2048) {
//         speed += 4096;
//     }

//     return {value, -speed};
// }

void Gaga::onSpiDataReceived(const SpiProtocol &spi) {
    // Turn the led off
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

    // gagaSerial.println("SPI: %x %x %x %x",
    //                    spi.motorPower[0],
    //                    spi.motorPower[1],
    //                    spi.motorPower[2],
    //                    spi.motorPower[3]);

    std::int32_t motorPower =
      math::lerp(spi.motorPower[0],
                 std::numeric_limits<std::int8_t>::min(),
                 std::numeric_limits<std::int8_t>::max(),
                 -2048,
                 2048);
    // motor.setPower(motorPower);
    //  motor.setPower(-1500);
    // gagaSerial.println("motor power: %d", motorPower);

    // Turn the led on
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    testSpeed_ = spi.motorPower[0];
}

// void Gaga::encoderConfReadTest() {
//     // Setup the encoder
//     constexpr std::uint8_t devAddr {0x36};
//     constexpr std::uint8_t confRegAddr {0x07};

//     // Read Configuration
//     gagaI2C.read(devAddr, confRegAddr, 2U);
//     while (gagaI2C.isBusy());    // Wait for finish
//     std::uint8_t *data = gagaI2C.__getData();

//     char b1[9];
//     char b2[9];

//     gagaSerial.println("conf: %s %s",
//                        math::printBits(data[0], b1),
//                        math::printBits(data[1], b2));

//     HAL_Delay(200);

//     constexpr std::uint8_t updatedConf[2] {0x03, 0x00};

//     gagaI2C.write(devAddr, confRegAddr, updatedConf, 2U);
//     HAL_Delay(1);
//     while (gagaI2C.isBusy());    // wait for waitting
//     HAL_Delay(5);                // wait for making effecting

//     // Lets read again
//     gagaI2C.read(devAddr, confRegAddr, 2U);
//     while (gagaI2C.isBusy());    // Wait for finish
//     data = gagaI2C.__getData();
//     gagaSerial.println("conf: %s %s",
//                        math::printBits(data[0], b1),
//                        math::printBits(data[1], b2));
// }


// void Gaga::encoderReadTest() {
//     HAL_Delay(1);    // align timing
//     gagaI2C.read(0x36, 0x0E, 2U);
//     while (gagaI2C.isBusy());
//     std::uint8_t *data    = gagaI2C.__getData();
//     const std::uint8_t hb = data[0];
//     const std::uint8_t lb = data[1];
//     std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) |
//     lb; HAL_Delay(1); gagaI2C.read(0x36, 0x1A, 1U); while (gagaI2C.isBusy());
//     data    = gagaI2C.__getData();
//     int agc = data[0];

//     gagaSerial.println("%d, %d", (int)(value), (int)agc);

//     HAL_Delay(10);
// }

Gaga gaga;

}    // namespace hal
}    // namespace cooboc
