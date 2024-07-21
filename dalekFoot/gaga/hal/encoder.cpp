#include "hal/encoder.h"
#include "hal/driver/i2c.h"
#include "hal/serial.h"

namespace cooboc {
namespace hal {
void Encoder::setup() { gagaI2C.setup(); }
void Encoder::begin() {
    // Start the timer for I2C
    gagaI2C.begin();
}


void Encoder::beginReading() {
    gagaI2C.read(0x36, 0x0E, 2U);
    //  | |
    //  | |
    // \   /
    //  \ /
    //   V
}

Encoder::EncoderReadings Encoder::getReadings() {
    // wait for data transmitting
    while (gagaI2C.isBusy()) {
        // do nothing
    }

    // TODO: make degradtion mapping

    std::array<I2C::I2CResult, 4U> result = hal::gagaI2C.getData();


    std::uint8_t *data {nullptr};
    std::uint16_t value[4] {0U, 0U, 0U, 0U};

    std::uint8_t hb {0U};
    std::uint8_t lb {0U};

    for (std::size_t i {0U}; i < 4U; ++i) {
        data     = result[i].dataBufferPtr;
        hb       = data[0];
        lb       = data[1];
        value[i] = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;
    }


    // Mock
    return {EncoderReading {value[0], Encoder::I2CStatus::OK},
            EncoderReading {value[1], Encoder::I2CStatus::OK},
            EncoderReading {value[2], Encoder::I2CStatus::OK},
            EncoderReading {value[3], Encoder::I2CStatus::OK}};
}

///// Following code is FOR Test, need to be refactor //////////////


void Encoder::i2cfrequencyTest() {
    for (std::uint32_t pre {7U}; pre < 100U; ++pre) {
        for (std::uint32_t period {20U}; period < 200U; period += 5U) {
            configTimer5(pre, period);
            statisticizeI2cReading(pre, period);
        }
    }
    while (true);
}

// Move this function to I2C?
void Encoder::configTimer5(const std::uint32_t pre,
                           const std::uint32_t period) {
    __HAL_TIM_SET_PRESCALER(&htim5, pre);
    __HAL_TIM_SET_AUTORELOAD(&htim5, period);
}

void Encoder::statisticizeI2cReading(const std::uint32_t pre,
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

Encoder gagaEncoder;

}    // namespace hal
}    // namespace cooboc