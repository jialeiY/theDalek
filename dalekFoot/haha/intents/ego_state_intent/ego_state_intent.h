#ifndef __INTENTS_EGO_STATE_INTENT_EGO_STATE_INTENT_H__
#define __INTENTS_EGO_STATE_INTENT_EGO_STATE_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class EgoStateIntent : public IntentBase {
  public:
    EgoStateIntent();
    virtual ~EgoStateIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc
#endif
