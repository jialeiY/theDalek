#ifndef __INTENTS_GAGA_INTENT_GAGA_INTENT_H__
#define __INTENTS_GAGA_INTENT_GAGA_INTENT_H__

#include "intents/intent_base.h"

namespace cooboc {
namespace intent {

class GagaIntent : public IntentBase {
  public:
    GagaIntent();
    virtual ~GagaIntent();
    virtual void setup() override;
    virtual void tick() override;
};


}    // namespace intent
}    // namespace cooboc
#endif
