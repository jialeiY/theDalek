#ifndef __INTENTS_COMMON_INTENT_MANAGER_H__
#define __INTENTS_COMMON_INTENT_MANAGER_H__

#include "intents/common/intent_base.h"

namespace cooboc {
namespace intents {
class IntentManager {
  public:
    IntentManager();
    void setup();
    void launch();
    void tick();

  private:
};

extern IntentManager intentManager;

}    // namespace intents
}    // namespace cooboc

#endif
