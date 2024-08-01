#ifndef __INTENTS_INTENT_MANAGER_H__
#define __INTENTS_INTENT_MANAGER_H__

#include <intents/intent_base.h>
#include <vector>

namespace cooboc {
namespace intent {


class IntentManager {
  public:
    IntentManager();
    virtual ~IntentManager();
    void setup();
    void tick();

  private:
    std::vector<IntentBase *> intents_;
};
}    // namespace intent
}    // namespace cooboc

#endif
