#include "intents/wheel_odometry_intent/wheel_odometry_intent.h"
#include <cstdint>
#include "hal/hal.h"
#include "intents/common/data_pool.h"
#include "intents/common/parameters.h"

namespace cooboc {
namespace intents {
void WheelOdometryIntent::setup() {
    data::wheelOdometryTopic.qualifier = data::Qualifier::BAD;
}

void WheelOdometryIntent::tick() {
    data::EncoderReadingTopic &currentEncoderReading = {
      data::encoderReadingTopic};
    if ((currentEncoderReading.qualifier == data::Qualifier::GOOD) &&
        (lastEncoderReading_.qualifier == data::Qualifier::GOOD)) {
        data::wheelOdometryTopic.qualifier = data::Qualifier::GOOD;
        data::Duration duration =
          currentEncoderReading.timestamp - lastEncoderReading_.timestamp;

        for (std::size_t i {0U}; i < 4U; ++i) {
            const data::EncoderReading &currentEncoderReading =
              data::encoderReadingTopic.encoder[i];
            data::wheelOdometryTopic.wheelSpeed[i] =
              calculateSingleWheelSpeed(currentEncoderReading,
                                        lastEncoderReading_.encoder[i],
                                        !parameters::kEncoderDirection[i]);
        }
    } else {
        data::wheelOdometryTopic.qualifier = data::Qualifier::BAD;
    }
    // hal::gagaSerial.println(
    //   "%d,%d,%d,%d",
    //   (int)(data::encoderReadingTriggerTopic.isTriggerSuccessful),
    //   (int)(currentEncoderReading.qualifier),
    //   (int)(currentEncoderReading.encoder[0].qualifier),
    //   (int)(currentEncoderReading.encoder[0].value));
    lastEncoderReading_ = currentEncoderReading;
}

data::WheelSpeed WheelOdometryIntent::calculateSingleWheelSpeed(
  const data::EncoderReading currentEncoderReading,
  const data::EncoderReading lastEncoderReading,
  const bool isReversed) {
    data::WheelSpeed ret {data::Qualifier::BAD, 0.0F};
    if ((currentEncoderReading.qualifier == data::Qualifier::GOOD) &&
        (lastEncoderReading.qualifier == data::Qualifier::GOOD)) {
        std::int32_t diff =
          currentEncoderReading.value - lastEncoderReading.value;
        if (diff > 2048) {
            diff -= 4096;
        }
        if (diff < -2048) {
            diff += 4096;
        }
        ret.qualifier = data::Qualifier::GOOD;
        ret.speed =
          isReversed ? -static_cast<float>(diff) : static_cast<float>(diff);
    }
    return ret;
}

}    // namespace intents
}    // namespace cooboc