#ifndef __INTENTS_WHEEL_ODOMETRY_INTENT_WHEEL_ODOMETRY_INTENT_H__
#define __INTENTS_WHEEL_ODOMETRY_INTENT_WHEEL_ODOMETRY_INTENT_H__

#include <cstdint>
#include "common/data_defs/circular_buffer.h"
#include "common/data_defs/duration.h"
#include "intents/common/data_pool.h"
#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {


class WheelOdometryIntent : public IntentBase {
  public:
    WheelOdometryIntent() = default;
    virtual void setup() override;
    virtual void tick() override;

  private:
    data::EncoderReadingTopic lastEncoderReading_;
    data::CircularBuffer<std::int32_t, 5U> accumulatedOdometry_[4U];

    data::WheelOdometry calculateSingleWheelOdometry(
      const data::EncoderReading currentEncoderReading,
      const data::EncoderReading lastEncoderReading,
      const data::Duration &duration,
      const bool isReversed);
};
}    // namespace intents
}    // namespace cooboc

#endif
