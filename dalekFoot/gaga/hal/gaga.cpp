#include "gaga.h"
#include <data/gh_protocol.h>
#include <cmath>
#include <cstdint>
#include <limits>
#include "common/data_defs/vehicle_request_topic.h"
#include "hal/board_def.h"
#include "hal/encoder.h"
#include "hal/motor.h"
#include "hal/serial.h"
#include "hal/spi.h"
#include "intents/common/data_pool.h"
#include "intents/common/intent_manager.h"
#include "stm32f4xx_hal.h"
#include "third_party/printf/printf.h"
#include "utils/math.h"
// #include "hal/driver/i2c.h"


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

    // Manually check the packet length and the Macro value
    static_assert(sizeof(cooboc::comm::HGPacket) == HG_PACKET_SIZE);
    static_assert(sizeof(cooboc::comm::GHPacket) == GH_PACKET_SIZE);

    static_assert((HG_PACKET_SIZE - 4U) % 4U == 0);    // For CRC calculating
    static_assert((GH_PACKET_SIZE - 4U) % 4U == 0);    // For CRC calculating

    static_assert(HG_PROTOCOL_SIZE == std::max(HG_PACKET_SIZE, GH_PACKET_SIZE));


    hasNewSpiPacket_ = false;

    // Init motors
    gagaMotors[0U].setup(GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1, &htim4, TIM_CHANNEL_1);
    gagaMotors[1U].setup(GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3, &htim4, TIM_CHANNEL_2);
    gagaMotors[2U].setup(GPIOD, GPIO_PIN_4, GPIOD, GPIO_PIN_5, &htim4, TIM_CHANNEL_3);
    gagaMotors[3U].setup(GPIOD, GPIO_PIN_6, GPIOD, GPIO_PIN_7, &htim4, TIM_CHANNEL_4);
    gagaMotors[4U].setup(GPIOD, GPIO_PIN_8, GPIOD, GPIO_PIN_9, &htim3, TIM_CHANNEL_3);
    gagaMotors[5U].setup(GPIOD, GPIO_PIN_10, GPIOD, GPIO_PIN_11, &htim2, TIM_CHANNEL_1);

    gagaSerial.setup();
    gagaSpi.setup([this](const comm::HGPacket &spi) { onSpiDataReceived(spi); });
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


bool validate(const comm::HGPacket &spiPacket) {
    const std::uint32_t &actualCrc {spiPacket.crc};
    const std::uint32_t expectedCrc = utils::math::calculateCrc(spiPacket);

    gagaSerial.println("crc %x %x", actualCrc, expectedCrc);
    return actualCrc == expectedCrc;
}

void Gaga::tick() {
    // Set the LED OFF
    LED1_OFF;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

    static uint64_t spiRequestId {0U};
    const comm::GHPacket *txPacket =
      reinterpret_cast<comm::GHPacket *>(data::vehicleResponseTopic.ghPacketBuffer);


    {    // Critical Area
        __disable_irq();
        if (hasNewSpiPacket_) {
            // Switch main memory and thread memory immediately
            const comm::HGPacket spiPacket {gagaSpi.getSpiPacketRef()};

            gagaSpi.setSpiPacket(*txPacket);
            __enable_irq();
            if (validate(spiPacket)) {
                // Make new request
                data::vehicleRequestTopic.requestId = ++spiRequestId;
                for (std::size_t i {0U}; i < 4U; ++i) {
                    for (std::size_t j {0U}; j < 10U; ++j) {
                        data::vehicleRequestTopic.wheel[i][j] = spiPacket.wheelsPlanning[i][j];
                    }
                }
            }
            hasNewSpiPacket_ = false;
        } else {
            __enable_irq();
        }
    }    // End of Critical Area

    intents::intentManager.tick();
    // Set the LED ON
    LED1_ON;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
}


void Gaga::onSpiDataReceived(const comm::HGPacket &spi) {
    hasNewSpiPacket_ = true;
    // // Turn the led off
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

    // // gagaSerial.println("SPI: %x %x %x %x",
    // //                    spi.motorPower[0],
    // //                    spi.motorPower[1],
    // //                    spi.motorPower[2],
    // //                    spi.motorPower[3]);

    // std::int32_t motorPower =
    //   utils::math::lerp(spi.motorPower[0],
    //                     std::numeric_limits<std::int8_t>::min(),
    //                     std::numeric_limits<std::int8_t>::max(),
    //                     -2048,
    //                     2048);
    // // motor.setPower(motorPower);
    // //  motor.setPower(-1500);
    // // gagaSerial.println("motor power: %d", motorPower);

    // // Turn the led on
    // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    // testSpeed_ = spi.motorPower[0];
}

Gaga gaga;

}    // namespace hal
}    // namespace cooboc
