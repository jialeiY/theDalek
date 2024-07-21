#include "intents/encoder_reading_intent/encoder_reading_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"


namespace cooboc {
namespace intents {
EncoderReadingIntent::EncoderReadingIntent() {}
void EncoderReadingIntent::setup() {}
void EncoderReadingIntent::tick() {
    // hal::gagaSerial.println("-");
    // wait for data transmitting
    while (hal::gagaI2C.isBusy()) {
        // do nothing
    }

    // hal::gagaSerial.println(".");
    hal::gagaI2C.__getData();
    std::uint8_t *data    = hal::gagaI2C.__getData();
    const std::uint8_t hb = data[0];
    const std::uint8_t lb = data[1];
    std::uint16_t value   = (static_cast<std::uint16_t>(hb & 0x0F) << 8U) | lb;

    data::encoderReadingOutput.encoder[0].value = value;
}
}    // namespace intents
}    // namespace cooboc