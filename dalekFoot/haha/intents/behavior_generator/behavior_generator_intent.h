#ifndef __INTENTS_BEHAVIOR_GENERATOR_BETAVIOR_GENERATOR_H__
#define __INTENTS_BEHAVIOR_GENERATOR_BETAVIOR_GENERATOR_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class BehaviorGeneratorIntent : public IntentBase {
  public:
    BehaviorGeneratorIntent();
    virtual ~BehaviorGeneratorIntent();
    virtual void setup() override;
    virtual void tick() override;
};

}    // namespace intent
}    // namespace cooboc
#endif
