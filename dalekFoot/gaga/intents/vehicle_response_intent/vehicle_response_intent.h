#ifndef __GAGA_INTENTS_VEHICLE_RESPONSE_INTENT_VEHICLE_RESPONSE_INTENT_H__
#define __GAGA_INTENTS_VEHICLE_RESPONSE_INTENT_VEHICLE_RESPONSE_INTENT_H__

#include <cstdint>
#include "common/data_defs/wheel_odometry.h"
#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class VehicleResponseIntent : public IntentBase {
  public:
    VehicleResponseIntent() = default;
    virtual void setup() override;
    virtual void tick() override;

  private:
    void clearVehicleResponseTopic();
    void reset();

    std::uint64_t lastRequestId_ {0U};
};
}    // namespace intents
}    // namespace cooboc

#endif
