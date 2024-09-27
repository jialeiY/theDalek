#include "data/codec/wheel_control_planning_codec.h"
#include <cstdint>
#include "gen/data/proto/wheel_control_planning.pb.h"
#include "intents/topics/vehicle_request_topic.h"


namespace cooboc {
namespace data {
proto::WheelControlPlanning convert(const intent::WheelControlPlanning &in) {
    proto::WheelControlPlanning out;
    for (std::size_t i {0U}; i < 10U; ++i) { out.add_encoderspeed(in.encoderSpeed[i]); }
    return out;
}
}    // namespace data
}    // namespace cooboc