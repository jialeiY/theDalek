#ifndef __INTENTS_EGO_MOTION_STATE_INTENT_EGO_MOTION_STATE_INTENT_H__
#define __INTENTS_EGO_MOTION_STATE_INTENT_EGO_MOTION_STATE_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class EgoMotionStateIntent : public IntentBase {
  public:
    EgoMotionStateIntent();
    virtual ~EgoMotionStateIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc
#endif
