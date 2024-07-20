#ifndef __INTENTS_DEBUG_DATA_INTENT_DEBUG_DATA_INTENT_H__
#define __INTENTS_DEBUG_DATA_INTENT_DEBUG_DATA_INTENT_H__

#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class DebugDataIntent : public IntentBase {
  public:
    DebugDataIntent() = default;
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intents
}    // namespace cooboc

#endif
