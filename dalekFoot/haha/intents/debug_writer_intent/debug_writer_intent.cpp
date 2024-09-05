
#include "intents/debug_writer_intent/debug_writer_intent.h"
#include <cstdint>
#include "data/codec/behavior_topic_codec.h"
#include "data/codec/ego_state_topic_codec.h"
#include "data/codec/motion_planning_debug_topic_codec.h"
#include "data/codec/odometry_topic_codec.h"
#include "data/codec/route_topic_codec.h"
#include "data/codec/trajectory_topic_codec.h"
#include "data/codec/vehicle_request_topic_codec.h"
#include "gen/data/proto/behavior_topic.pb.h"
#include "gen/data/proto/ego_state_topic.pb.h"
#include "gen/data/proto/motion_planning_debug_topic.pb.h"
#include "gen/data/proto/motion_planning_topic.pb.h"
#include "gen/data/proto/odometry_topic.pb.h"
#include "gen/data/proto/route_topic.pb.h"
#include "gen/data/proto/trajectory_topic.pb.h"
#include "gen/data/proto/vehicle_request_topic.pb.h"
#include "intents/topics/odometry_topic.h"
#include "intents/topics/topics.h"
#include "intents/topics/vehicle_request_topic.h"
#include "utils/time.h"

namespace cooboc {
namespace intent {

namespace {}    // namespace

DebugWriterIntent::DebugWriterIntent() {
    mcapTopicConverterList_.push_back(
      new McapTopicConverter(&vehicleResponseTopic, "/vehicle/response"));
    mcapTopicConverterList_.push_back(
      new McapTopicConverter<cooboc::intent::EgoStateTopic>(&egoStateTopic, "/ego_state"));
    mcapTopicConverterList_.push_back(new McapTopicConverter(&odometryTopic, "/odometry"));
    mcapTopicConverterList_.push_back(new McapTopicConverter(&behaviorTopic, "/planning/behavior"));
    mcapTopicConverterList_.push_back(new McapTopicConverter(&routeTopic, "/planning/route"));
    mcapTopicConverterList_.push_back(
      new McapTopicConverter(&trajectoryTopic, "/planning/trajectory"));
    mcapTopicConverterList_.push_back(
      new McapTopicConverter(&motionPlanningTopic, "/planning/motion"));
    mcapTopicConverterList_.push_back(
      new McapTopicConverter(&motionPlanningDebugTopic, "/debug/motion_planning"));
    mcapTopicConverterList_.push_back(
      new McapTopicConverter(&vehicleRequestTopic, "/vehicle/request"));
}


DebugWriterIntent::~DebugWriterIntent() {
    while (mcapTopicConverterList_.size() > 0U) {
        IMcapTopicConverter *c = mcapTopicConverterList_.back();
        mcapTopicConverterList_.pop_back();
        delete c;
    }

    writer_.close();
}

void DebugWriterIntent::setup() {
    std::ignore = writer_.open("runtime/output.mcap", mcap::McapWriterOptions("haha"));

    for (IMcapTopicConverter *mcapTopicPtr : mcapTopicConverterList_) {
        mcapTopicPtr->setupSchema();
        writer_.addSchema(*(mcapTopicPtr->getSchema()));
        mcapTopicPtr->setupChannel();
        writer_.addChannel(*(mcapTopicPtr->getChannel()));
    }
}
std::uint32_t sequence {0U};
void DebugWriterIntent::tick() {
    systemDebugTopic.cycleEndTime = utils::time::nanoseconds();
    const std::uint64_t duration  = systemDebugTopic.cycleEndTime - systemDebugTopic.cycleStartTime;
    std::printf("druation: %lu\r\n", duration);

    for (IMcapTopicConverter *mcapTopicPtr : mcapTopicConverterList_) {
        mcapTopicPtr->convertMessage(writer_);
    }
}
}    // namespace intent
}    // namespace cooboc