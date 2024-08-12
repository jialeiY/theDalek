#ifndef __INTENTS_BEHAVIOR_INTENT_BEHAVIOR_INTENT_H__
#define __INTENTS_BEHAVIOR_INTENT_BEHAVIOR_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class BehaviorIntent : public IntentBase {
  public:
    BehaviorIntent();
    virtual ~BehaviorIntent();
    virtual void setup() override;
    virtual void tick() override;
};

}    // namespace intent
}    // namespace cooboc
#endif
