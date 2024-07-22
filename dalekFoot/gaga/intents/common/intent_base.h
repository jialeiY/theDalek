#ifndef __COMMON_INTENT_BASE_H__
#define __COMMON_INTENT_BASE_H__

namespace cooboc {
namespace intents {

class IntentBase {
  public:
    virtual void setup() = 0;
    virtual void tick()  = 0;
};


}    // namespace intents
}    // namespace cooboc

#endif
