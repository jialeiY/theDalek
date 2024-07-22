#ifndef __COMMON_INTENT_MANAGER_H__
#define __COMMON_INTENT_MANAGER_H__

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
    std::array<IntentBase *, 6U> intents_;
};

extern IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc

#endif
