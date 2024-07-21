#ifndef __INTENTS_WHEEL_ODOMETRY_INTENT_WHEEL_ODOMETRY_INTENT_H__
#define __INTENTS_WHEEL_ODOMETRY_INTENT_WHEEL_ODOMETRY_INTENT_H__

#include <cstdint>
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
    data::EncoderReading lastEncoderReading_[4U];

    data::WheelSpeed calculateSingleWheelSpeed(
      const data::EncoderReading currentEncoderReading,
      const data::EncoderReading lastEncoderReading);
};
}    // namespace intents
}    // namespace cooboc

#endif
