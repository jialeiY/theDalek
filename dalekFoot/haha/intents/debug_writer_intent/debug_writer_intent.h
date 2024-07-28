#ifndef __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__
#define __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__


#include <intents/intent_base.h>
#include <mcap/writer.hpp>


namespace cooboc {
namespace intent {
class DebugWriterIntent : public IntentBase {
  public:
    DebugWriterIntent();
    virtual ~DebugWriterIntent();
    void setup() override;
    void tick() override;

  private:
    mcap::McapWriter writer_;
    mcap::Schema *planningRequestTopicSchema_ {nullptr};
    mcap::Channel *planningRequestTopicChannel_ {nullptr};
};
}    // namespace intent
}    // namespace cooboc

#endif
