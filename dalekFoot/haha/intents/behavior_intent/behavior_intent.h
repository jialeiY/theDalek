#ifndef __INTENTS_BEHAVIOR_INTENT_BEHAVIOR_INTENT_H__
#define __INTENTS_BEHAVIOR_INTENT_BEHAVIOR_INTENT_H__

#include "data/defs/behavior_id.h"
#include "intents/intent_base.h"
#include "intents/topics/behavior_topic.h"

namespace cooboc {
namespace intent {

class BehaviorIntent : public IntentBase {
  public:
    BehaviorIntent();
    virtual ~BehaviorIntent();
    virtual void setup() override;
    virtual void tick() override;

  private:
    static data::BehaviorId makeNewBehaviorId();
    void outputStopBehavior();
    void outputMotionBehavior();

    intent::BehaviorTopic behaviorTopic_ {};
    data::BehaviorId lastStopBehaviorId_ {data::kInvalidBehaviorId};
    data::BehaviorId lastMotionBehaviorId_ {data::kInvalidBehaviorId};
};

}    // namespace intent
}    // namespace cooboc
#endif
