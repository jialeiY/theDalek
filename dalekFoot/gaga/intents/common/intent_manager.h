#ifndef __INTENTS_COMMON_INTENT_MANAGER_H__
#define __INTENTS_COMMON_INTENT_MANAGER_H__

#include <array>
#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class IntentManager {
  public:
    IntentManager();
    void setup();
    void tick();

  private:
    std::array<IntentBase *, 4U> intents_;
};

extern IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc

#endif
