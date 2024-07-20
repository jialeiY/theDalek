#ifndef __INTENT_ENCODER_READING_TRIGGER_INTENT_ENCODER_READING_TRIGGER_INTENT_H__
#define __INTENT_ENCODER_READING_TRIGGER_INTENT_ENCODER_READING_TRIGGER_INTENT_H__

#include "intents/common/intent_base.h"


namespace cooboc {
namespace intents {
class EncoderReadingTriggerIntent : public IntentBase {
  public:
    EncoderReadingTriggerIntent();
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intents
}    // namespace cooboc

#endif
