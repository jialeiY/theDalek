#ifndef __INTENTS_POWER_CONTROLLING_INTENT_POWER_CONTROLLING_INTENT_H__
#define __INTENTS_POWER_CONTROLLING_INTENT_POWER_CONTROLLING_INTENT_H__

#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class PowerControllingIntent : public IntentBase {
    virtual void setup() override;
};
}    // namespace intents
}    // namespace cooboc


#endif
