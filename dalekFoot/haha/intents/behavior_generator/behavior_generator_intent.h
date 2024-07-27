#ifndef __INTENTS_BEHAVIOR_GENERATOR_BETAVIOR_GENERATOR_H__
#define __INTENTS_BEHAVIOR_GENERATOR_BETAVIOR_GENERATOR_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intents {

class BehaviorGeneratorIntent : public IntentBase {
  public:
    virtual void setup() override {}
    virtual void tick() override {}
};

}    // namespace intents
}    // namespace cooboc
#endif
