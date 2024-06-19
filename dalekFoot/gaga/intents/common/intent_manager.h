#ifndef __INTENTS_COMMON_INTENT_MANAGER_H__
#define __INTENTS_COMMON_INTENT_MANAGER_H__

#include "intents/common/intent_base.h"
#include "intents/common/pub_sub_stub.h"

namespace cooboc {
namespace intents {
class IntentManager {
  public:
    IntentManager();
    void setup();
    void launch();
    void tick();

  private:
    PubSubStub pubSubStub_;
};

extern IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc

#endif
