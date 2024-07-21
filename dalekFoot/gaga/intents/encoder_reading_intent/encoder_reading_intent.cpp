#include "intents/encoder_reading_intent/encoder_reading_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"


namespace cooboc {
namespace intents {
EncoderReadingIntent::EncoderReadingIntent() {}
void EncoderReadingIntent::setup() {}
void EncoderReadingIntent::tick() {
    hal::Encoder::EncoderReadings readings {hal::gagaEncoder.getReadings()};

    for (std::size_t i {0U}; i < readings.size(); ++i) {
        data::encoderReadingTopic.encoder[i].value = readings[i].value;
        // TODO
        data::encoderReadingTopic.encoder[i].qualifier = data::Qualifier::GOOD;
    }
}
}    // namespace intents
}    // namespace cooboc