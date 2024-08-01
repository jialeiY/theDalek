#define MCAP_IMPLEMENTATION
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <cstdint>
#include <mcap/writer.hpp>
#include "data/codec/odometry_topic_codec.h"
#include "data/codec/planning_request_topic_codec.h"
#include "gen/data/proto/odometry_topic.pb.h"
#include "gen/data/proto/planning_request_topic.pb.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/topics.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

namespace {


// Recursively adds all `fd` dependencies to `fd_set`.
void fdSetInternal(google::protobuf::FileDescriptorSet &fd_set,
                   std::unordered_set<std::string> &files,
                   const google::protobuf::FileDescriptor *fd) {
    for (int i = 0; i < fd->dependency_count(); ++i) {
        const auto *dep    = fd->dependency(i);
        auto [_, inserted] = files.insert(dep->name());
        if (!inserted)
            continue;
        fdSetInternal(fd_set, files, fd->dependency(i));
    }
    fd->CopyTo(fd_set.add_file());
}

// Returns a serialized google::protobuf::FileDescriptorSet containing
// the necessary google::protobuf::FileDescriptor's to describe d.
std::string fdSet(const google::protobuf::Descriptor *d) {
    std::string res;
    std::unordered_set<std::string> files;
    google::protobuf::FileDescriptorSet fd_set;
    fdSetInternal(fd_set, files, d->file());
    return fd_set.SerializeAsString();
}

mcap::Schema createSchema(const google::protobuf::Descriptor *d) {
    mcap::Schema schema(d->full_name(), "protobuf", fdSet(d));
    return schema;
}
}    // namespace

DebugWriterIntent::DebugWriterIntent() :
    planningRequestTopicSchema_ {nullptr},
    planningRequestTopicChannel_ {nullptr},
    odometryTopicSchema_ {nullptr},
    odometryTopicChannel_ {nullptr} {}
DebugWriterIntent::~DebugWriterIntent() {
    if (planningRequestTopicSchema_ != nullptr) {
        delete planningRequestTopicSchema_;
    }
    if (planningRequestTopicChannel_ != nullptr) {
        delete planningRequestTopicChannel_;
    }
    if (odometryTopicSchema_ != nullptr) {
        delete odometryTopicSchema_;
    }
    if (odometryTopicChannel_ != nullptr) {
        delete odometryTopicChannel_;
    }
    writer_.close();
}

void DebugWriterIntent::setup() {
    std::ignore =
      writer_.open("runtime/output.mcap", mcap::McapWriterOptions("haha"));

    // Create and Register Schema
    planningRequestTopicSchema_ = new mcap::Schema();
    *planningRequestTopicSchema_ =
      createSchema(cooboc::proto::PlanningRequestTopic::descriptor());
    writer_.addSchema(*planningRequestTopicSchema_);

    // Create and Register Channel
    planningRequestTopicChannel_  = new mcap::Channel();
    *planningRequestTopicChannel_ = mcap::Channel(
      "/planning/behavior", "protobuf", planningRequestTopicSchema_->id);
    writer_.addChannel(
      *planningRequestTopicChannel_);    // Assigned channel id written to
    // planningRequestTopicChannel.id

    // Odometry Schema
    odometryTopicSchema_ = new mcap::Schema();
    *odometryTopicSchema_ =
      createSchema(cooboc::proto::OdometryTopic::descriptor());
    writer_.addSchema(*odometryTopicSchema_);

    // Register channel
    odometryTopicChannel_ = new mcap::Channel();
    *odometryTopicChannel_ =
      mcap::Channel("/odometry", "protobuf", odometryTopicSchema_->id);
    writer_.addChannel(*odometryTopicChannel_);
}

void DebugWriterIntent::tick() {
    static std::uint32_t sequence {0U};

    {
        proto::PlanningRequestTopic payloadMsg =
          data::convert(planningRequestTopic);
        const std::string payload = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = planningRequestTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data     = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize = payload.size();

        std::ignore = writer_.write(message);
    }
    {
        proto::OdometryTopic payloadMsg = data::convert(odometryTopic);
        const std::string payload       = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = odometryTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data     = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize = payload.size();

        std::ignore = writer_.write(message);
    }
}
}    // namespace intent
}    // namespace cooboc