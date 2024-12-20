#ifndef __INTENTS_ODOMETRY_INTENT_ODOMETRY_INTENT_H__
#define __INTENTS_ODOMETRY_INTENT_ODOMETRY_INTENT_H__

#include <cstdint>
#include <random>
#include "intents/intent_base.h"

namespace cooboc {
namespace intent {
class OdometryIntent : public IntentBase {
  public:
    OdometryIntent();
    virtual ~OdometryIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    bool isInitialized_ {false};
    std::int64_t encoderOdometry_[4U];

    std::random_device randomDev_;
    std::mt19937 randomGen_;
    std::normal_distribution<float> randomDistribution_;
};
}    // namespace intent
}    // namespace cooboc

#endif
