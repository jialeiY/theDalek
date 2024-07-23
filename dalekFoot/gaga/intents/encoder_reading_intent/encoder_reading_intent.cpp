#include "intents/encoder_reading_intent/encoder_reading_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"


namespace cooboc {
namespace intents {
EncoderReadingIntent::EncoderReadingIntent() {}
void EncoderReadingIntent::setup() {}
void EncoderReadingIntent::tick() {
    const data::EncoderReadingTriggerTopic &triggerTopic {
      data::encoderReadingTriggerTopic};
    data::encoderReadingTopic.timestamp = triggerTopic.timestamp;
    if (triggerTopic.isTriggerSuccessful) {
        data::encoderReadingTopic.qualifier = data::Qualifier::GOOD;
        hal::Encoder::EncoderReadings readings {hal::gagaEncoder.getReadings()};
        for (std::size_t i {0U}; i < readings.size(); ++i) {
            data::encoderReadingTopic.encoder[i].value = readings[i].value;
            // TODO
            data::encoderReadingTopic.encoder[i].qualifier =
              data::Qualifier::GOOD;
        }
    } else {
        data::encoderReadingTopic.qualifier = data::Qualifier::BAD;
    }
}
}    // namespace intents
}    // namespace cooboc