#ifndef __INTENTS_POSITIONING_INTENT_POSITIONING_INTENT_H__
#define __INTENTS_POSITIONING_INTENT_POSITIONING_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {
class PositioningIntent : public IntentBase {
  public:
    PositioningIntent();
    virtual ~PositioningIntent();
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intent
}    // namespace cooboc

#endif
