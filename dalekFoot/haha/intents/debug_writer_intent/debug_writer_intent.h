#ifndef __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__
#define __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__


#include <intents/intent_base.h>
#include <mcap/writer.hpp>
#include <string>
#include <vector>
#include "data/codec/behavior_topic_codec.h"
#include "data/codec/ego_state_topic_codec.h"
#include "data/codec/motion_planning_debug_topic_codec.h"
#include "data/codec/motion_planning_topic_codec.h"
#include "data/codec/odometry_topic_codec.h"
#include "data/codec/route_topic_codec.h"
#include "data/codec/system_debug_codec.h"
#include "data/codec/trajectory_topic_codec.h"
#include "data/codec/vehicle_request_topic_codec.h"
#include "data/codec/vehicle_response_topic_codec.h"
#include "intents/debug_writer_intent/mcap_helper.h"
#include "utils/time.h"

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
    virtual void setupSchema()  = 0;
    virtual void setupChannel() = 0;
    mcap::Schema *getSchema(void) const { return schema_; }
    mcap::Channel *getChannel(void) const { return channel_; }
    virtual mcap::Message convertMessage(mcap::McapWriter &writer) const = 0;

  protected:
    mcap::Schema *schema_ {nullptr};
    mcap::Channel *channel_ {nullptr};
    const std::string channelName_;
};

template<typename TInternal>
class McapTopicConverter : public IMcapTopicConverter {
  public:
    McapTopicConverter(TInternal *topic, const std::string &channelName) :
        IMcapTopicConverter {channelName},
        topic_ {topic} {}
    McapTopicConverter(const McapTopicConverter &) = delete;
    McapTopicConverter(McapTopicConverter &&)      = delete;
    void operator=(const McapTopicConverter &)     = delete;
    void operator=(McapTopicConverter &&)          = delete;
    virtual ~McapTopicConverter() {}
    virtual void setupSchema() override {
        schema_     = new mcap::Schema();
        using TMcap = decltype(data::convert(*topic_));
        *schema_    = mcap_helper::createSchema(TMcap::descriptor());
    }
    virtual void setupChannel() override {
        channel_ = new mcap::Channel(channelName_, "protobuf", schema_->id);
    }

    virtual mcap::Message convertMessage(mcap::McapWriter &writer) const {
        auto payloadMsg = data::convert(*topic_);

        const std::string payload = payloadMsg.SerializeAsString();
        extern std::uint32_t sequence;

        mcap::Message message;
        message.channelId   = channel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();

        writer.write(message);

        return message;
    }

  private:
    TInternal *topic_;
};

class DebugWriterIntent : public IntentBase {
  public:
    DebugWriterIntent();
    virtual ~DebugWriterIntent();
    void setup() override;
    void tick() override;

  private:
    mcap::McapWriter writer_;
    std::vector<IMcapTopicConverter *> mcapTopicConverterList_ {};
};
}    // namespace intent
}    // namespace cooboc

#endif
