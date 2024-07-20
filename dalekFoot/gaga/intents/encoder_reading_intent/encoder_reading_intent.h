#ifndef __INTENT_ENCODER_READING_INTENT_ENCODER_READING_INTENT_H__
#define __INTENT_ENCODER_READING_INTENT_ENCODER_READING_INTENT_H__

#include "intents/common/intent_base.h"


namespace cooboc {
namespace intents {
class EncoderReadingIntent : public IntentBase {
  public:
    EncoderReadingIntent();
    virtual void setup() override;
    virtual void tick() override;
};
}    // namespace intents
}    // namespace cooboc

#endif
