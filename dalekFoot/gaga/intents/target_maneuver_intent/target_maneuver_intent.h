#ifndef __INTENTS_TARGET_MANEUVER_INTENT_TARGET_MANEUVER_INTENT_H__
#define __INTENTS_TARGET_MANEUVER_INTENT_TARGET_MANEUVER_INTENT_H__


#include <cstdint>
#include "intents/common/data_pool.h"
#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class TargetManeuverIntent : public IntentBase {
  public:
    TargetManeuverIntent() = default;
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intents
}    // namespace cooboc


#endif