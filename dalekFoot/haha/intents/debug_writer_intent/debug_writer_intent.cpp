#define MCAP_IMPLEMENTATION

#include "intents/debug_writer_intent/debug_writer_intent.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <cstdint>
#include <mcap/writer.hpp>
#include "data/codec/behavior_topic_codec.h"
#include "data/codec/ego_state_topic_codec.h"
#include "data/codec/motion_planning_debug_topic_codec.h"
#include "data/codec/odometry_topic_codec.h"
#include "data/codec/route_topic_codec.h"
#include "data/codec/trajectory_topic_codec.h"
#include "gen/data/proto/behavior_topic.pb.h"
#include "gen/data/proto/ego_state_topic.pb.h"
#include "gen/data/proto/motion_planning_debug_topic.pb.h"
#include "gen/data/proto/odometry_topic.pb.h"
#include "gen/data/proto/route_topic.pb.h"
#include "gen/data/proto/trajectory_topic.pb.h"
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
    odometryTopicChannel_ {nullptr},
    egoStateTopicSchema_ {nullptr},
    egoStateTopicChannel_ {nullptr},
    routeTopicSchema_ {nullptr},
    routeTopicChannel_ {nullptr},
    trajectoryTopicSchema_ {nullptr},
    trajectoryTopicChannel_ {nullptr},
    motionPlanningDebugTopicSchema_ {nullptr},
    motionPlanningDebugTopicChannel_ {nullptr} {}
DebugWriterIntent::~DebugWriterIntent() {
    if (planningRequestTopicSchema_ != nullptr) {
        delete planningRequestTopicSchema_;
    }
    if (planningRequestTopicChannel_ != nullptr) {
        delete planningRequestTopicChannel_;
    }

    // OdometryTopic
    if (odometryTopicSchema_ != nullptr) {
        delete odometryTopicSchema_;
    }
    if (odometryTopicChannel_ != nullptr) {
        delete odometryTopicChannel_;
    }

    // EgoStateTopic
    if (egoStateTopicSchema_ != nullptr) {
        delete egoStateTopicSchema_;
    }
    if (egoStateTopicChannel_ != nullptr) {
        delete egoStateTopicChannel_;
    }

    // RouteTopic
    if (routeTopicSchema_ != nullptr) {
        delete routeTopicSchema_;
    }
    if (routeTopicChannel_ != nullptr) {
        delete routeTopicChannel_;
    }

    // TrajectoryTopic
    if (trajectoryTopicSchema_ != nullptr) {
        delete trajectoryTopicSchema_;
    }
    if (trajectoryTopicChannel_ != nullptr) {
        delete trajectoryTopicChannel_;
    }


    if (motionPlanningDebugTopicSchema_ != nullptr) {
        delete motionPlanningDebugTopicSchema_;
    }
    if (motionPlanningDebugTopicChannel_ != nullptr) {
        delete motionPlanningDebugTopicChannel_;
    }
    writer_.close();
}

void DebugWriterIntent::setup() {
    std::ignore = writer_.open("runtime/output.mcap", mcap::McapWriterOptions("haha"));

    // Create and Register Schema
    planningRequestTopicSchema_  = new mcap::Schema();
    *planningRequestTopicSchema_ = createSchema(cooboc::proto::BehaviorTopic::descriptor());
    writer_.addSchema(*planningRequestTopicSchema_);

    // Create and Register Channel
    planningRequestTopicChannel_ = new mcap::Channel();
    *planningRequestTopicChannel_ =
      mcap::Channel("/planning/behavior", "protobuf", planningRequestTopicSchema_->id);
    writer_.addChannel(*planningRequestTopicChannel_);    // Assigned channel id written to
    // planningRequestTopicChannel.id

    // Odometry Schema
    odometryTopicSchema_  = new mcap::Schema();
    *odometryTopicSchema_ = createSchema(cooboc::proto::OdometryTopic::descriptor());
    writer_.addSchema(*odometryTopicSchema_);
    // Register channel
    odometryTopicChannel_  = new mcap::Channel();
    *odometryTopicChannel_ = mcap::Channel("/odometry", "protobuf", odometryTopicSchema_->id);
    writer_.addChannel(*odometryTopicChannel_);

    // EgoStateTopic
    // Register Schema
    egoStateTopicSchema_  = new mcap::Schema();
    *egoStateTopicSchema_ = createSchema(cooboc::proto::EgoStateTopic::descriptor());
    writer_.addSchema(*egoStateTopicSchema_);
    // Register channel
    egoStateTopicChannel_  = new mcap::Channel();
    *egoStateTopicChannel_ = mcap::Channel("/ego_state", "protobuf", egoStateTopicSchema_->id);
    writer_.addChannel(*egoStateTopicChannel_);


    // Route Topic
    // route Schema
    routeTopicSchema_  = new mcap::Schema();
    *routeTopicSchema_ = createSchema(cooboc::proto::RouteTopic::descriptor());
    writer_.addSchema(*routeTopicSchema_);
    // Register channel
    routeTopicChannel_  = new mcap::Channel();
    *routeTopicChannel_ = mcap::Channel("/route", "protobuf", routeTopicSchema_->id);
    writer_.addChannel(*routeTopicChannel_);

    // Trajectory Topic
    // route Schema
    trajectoryTopicSchema_  = new mcap::Schema();
    *trajectoryTopicSchema_ = createSchema(cooboc::proto::TrajectoryTopic::descriptor());
    writer_.addSchema(*trajectoryTopicSchema_);
    // Register channel
    trajectoryTopicChannel_  = new mcap::Channel();
    *trajectoryTopicChannel_ = mcap::Channel("/trajectory", "protobuf", trajectoryTopicSchema_->id);
    writer_.addChannel(*trajectoryTopicChannel_);

    // MotionPlanningDebugTopic
    // route Schema
    motionPlanningDebugTopicSchema_ = new mcap::Schema();
    *motionPlanningDebugTopicSchema_ =
      createSchema(cooboc::proto::MotionPlanningDebugTopic::descriptor());
    writer_.addSchema(*motionPlanningDebugTopicSchema_);

    // Register channel
    motionPlanningDebugTopicChannel_ = new mcap::Channel();
    *motionPlanningDebugTopicChannel_ =
      mcap::Channel("/debug/motion_planning", "protobuf", motionPlanningDebugTopicSchema_->id);
    writer_.addChannel(*motionPlanningDebugTopicChannel_);
}

void DebugWriterIntent::tick() {
    static std::uint32_t sequence {0U};

    // Planning Request
    {
        proto::BehaviorTopic payloadMsg = data::convert(behaviorTopic);
        const std::string payload       = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = planningRequestTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();

        std::ignore = writer_.write(message);
    }
    // Odometry
    {
        proto::OdometryTopic payloadMsg = data::convert(odometryTopic);
        const std::string payload       = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = odometryTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();

        std::ignore = writer_.write(message);
    }
    // EgoState
    {
        proto::EgoStateTopic payloadMsg = data::convert(egoStateTopic);
        const std::string payload       = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = egoStateTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();

        std::ignore = writer_.write(message);
    }

    // Route
    {
        proto::RouteTopic payloadMsg = data::convert(routeTopic);
        const std::string payload    = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = routeTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();
        std::ignore         = writer_.write(message);
    }

    // Trajectory
    {
        proto::TrajectoryTopic payloadMsg = data::convert(trajectoryTopic);
        const std::string payload         = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = trajectoryTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();
        std::ignore         = writer_.write(message);
    }

    // Motion Planning Debug Topic
    {
        proto::MotionPlanningDebugTopic payloadMsg = data::convert(motionPlanningDebugTopic);
        const std::string payload                  = payloadMsg.SerializeAsString();

        mcap::Message message;
        message.channelId   = motionPlanningDebugTopicChannel_->id;
        message.sequence    = sequence++;
        message.logTime     = utils::time::nanoseconds();
        message.publishTime = utils::time::nanoseconds();
        message.data        = reinterpret_cast<const std::byte *>(payload.data());
        message.dataSize    = payload.size();
        std::ignore         = writer_.write(message);
    }
}
}    // namespace intent
}    // namespace cooboc