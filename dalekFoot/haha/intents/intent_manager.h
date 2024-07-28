#ifndef __INTENTS_INTENT_MANAGER_H__
#define __INTENTS_INTENT_MANAGER_H__

#include <intents/intent_base.h>
#include <array>

namespace cooboc {
namespace intent {


class IntentManager {
  public:
    IntentManager();
    virtual ~IntentManager();
    void setup();
    void tick();

  private:
    std::array<IntentBase *, 2U> intents_;
};
}    // namespace intent
}    // namespace cooboc

#endif
