#ifndef __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__
#define __INTENTS_DEBUG_WRITER_INTENT_DEBUG_WRITER_INTENT_H__


#include <intents/intent_base.h>
#include <mcap/writer.hpp>
#include <string>
#include <vector>
#include "data/codec/behavior_topic_codec.h"
#include "data/codec/ego_state_topic_codec.h"
#include "data/codec/motion_planning_debug_topic_codec.h"
#include "data/codec/odometry_topic_codec.h"
#include "data/codec/route_topic_codec.h"
#include "data/codec/trajectory_topic_codec.h"
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
class McapTopicCoonverter : public IMcapTopicConverter {
  public:
    McapTopicCoonverter(TInternal *topic, const std::string &channelName) :
        IMcapTopicConverter {channelName},
        topic_ {topic}

    //,        descriptor_ {d}
    {}
    McapTopicCoonverter(const McapTopicCoonverter &) = delete;
    McapTopicCoonverter(McapTopicCoonverter &&)      = delete;
    void operator=(const McapTopicCoonverter &)      = delete;
    void operator=(McapTopicCoonverter &&)           = delete;
    virtual ~McapTopicCoonverter() {}
    virtual void setupSchema() override {
        schema_     = new mcap::Schema();
        using TMcap = decltype(data::convert(*topic_));
        // auto mcapTopic = data::convert(*topic_);
        // using T2       = decltype(mcapTopic);

        // std::printf("this type: %s, proto topic: %s, T2: %s\r\n",
        //             typeid(*this).name(),
        //             typeid(TMcap).name(),
        //             typeid(T2).name());
        *schema_ = mcap_helper::createSchema(TMcap::descriptor());
        //*schema_ = mcap_helper::createSchema(cooboc::proto::BehaviorTopic::descriptor());
        //*schema_ = mcap_helper::createSchema(descriptor_);
    }
    virtual void setupChannel() override {
        channel_ = new mcap::Channel(channelName_, "protobuf", schema_->id);
    }

    virtual mcap::Message convertMessage(mcap::McapWriter &writer) const {
        auto payloadMsg = data::convert(*topic_);

        const std::string payload = payloadMsg.SerializeAsString();
        extern std::uint32_t sequence;
        // std::printf("msg: %s, velo: %f\r\n", payload.c_str(),
        // payloadMsg.velocity().orientation());

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
    // const google::protobuf::Descriptor *descriptor_;
};

class DebugWriterIntent : public IntentBase {
  public:
    DebugWriterIntent();
    virtual ~DebugWriterIntent();
    void setup() override;
    void tick() override;

  private:
    mcap::McapWriter writer_;
    // mcap::Schema *planningRequestTopicSchema_ {nullptr};
    // mcap::Channel *planningRequestTopicChannel_ {nullptr};

    // mcap::Schema *odometryTopicSchema_ {nullptr};
    // mcap::Channel *odometryTopicChannel_ {nullptr};

    // mcap::Schema *egoStateTopicSchema_ {nullptr};
    // mcap::Channel *egoStateTopicChannel_ {nullptr};

    // mcap::Schema *routeTopicSchema_ {nullptr};
    // mcap::Channel *routeTopicChannel_ {nullptr};

    // mcap::Schema *trajectoryTopicSchema_ {nullptr};
    // mcap::Channel *trajectoryTopicChannel_ {nullptr};


    // mcap::Schema *motionPlanningDebugTopicSchema_ {nullptr};
    // mcap::Channel *motionPlanningDebugTopicChannel_ {nullptr};

    std::vector<IMcapTopicConverter *> mcapTopicConverterList_ {};
};
}    // namespace intent
}    // namespace cooboc

#endif
