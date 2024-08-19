#ifndef __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__
#define __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__


#include <intents/intent_base.h>
#include <mcap/writer.hpp>
#include <string>


namespace cooboc {
namespace intent {


class IMcapTopicConverter {
  public:
    IMcapTopicConverter(const std::string channelName) :
        schema_ {nullptr},
        channel_ {nullptr},
        channelName_ {channelName} {};
    IMcapTopicConverter(const IMcapTopicConverter &) = delete;
    IMcapTopicConverter(IMcapTopicConverter &&)      = delete;
    void operator=(const IMcapTopicConverter &)      = delete;
    void operator=(IMcapTopicConverter &&)           = delete;
    virtual ~IMcapTopicConverter() {
        if (schema_ != nullptr) {
            delete schema_;
        }
        if (channel_ != nullptr) {
            delete channel_;
        }
    }
    virtual void setup() = 0;

  private:
    mcap::Schema *schema_ {nullptr};
    mcap::Channel *channel_ {nullptr};
    const std::string channelName_;
};

template<typename T>
class McapTopicCoonverter : public IMcapTopicConverter {
  public:
    McapTopicCoonverter(std::string channelName) : IMcapTopicConverter {channelName} {}
    McapTopicCoonverter(const McapTopicCoonverter &) = delete;
    McapTopicCoonverter(McapTopicCoonverter &&)      = delete;
    void operator=(const McapTopicCoonverter &)      = delete;
    void operator=(McapTopicCoonverter &&)           = delete;
    virtual ~McapTopicCoonverter() {}
    virtual void setup() {
        schema_  = new mcap::Schema();
        *schema_ = createSchema(T::descriptor());

        channel_  = new mcap::Channel();
        *channel_ = mcap::Channel()
    }
};

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

    mcap::Schema *odometryTopicSchema_ {nullptr};
    mcap::Channel *odometryTopicChannel_ {nullptr};

    mcap::Schema *egoStateTopicSchema_ {nullptr};
    mcap::Channel *egoStateTopicChannel_ {nullptr};

    mcap::Schema *routeTopicSchema_ {nullptr};
    mcap::Channel *routeTopicChannel_ {nullptr};

    mcap::Schema *trajectoryTopicSchema_ {nullptr};
    mcap::Channel *trajectoryTopicChannel_ {nullptr};


    mcap::Schema *motionPlanningDebugTopicSchema_ {nullptr};
    mcap::Channel *motionPlanningDebugTopicChannel_ {nullptr};
};
}    // namespace intent
}    // namespace cooboc

#endif
