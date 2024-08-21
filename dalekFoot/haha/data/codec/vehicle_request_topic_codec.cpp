#include "data/codec/vehicle_request_topic_codec.h"
#include "data/codec/wheel_control_planning_codec.h"
#include "gen/data/proto/vehicle_request_topic.pb.h"
#include "gen/data/proto/wheel_control_planning.pb.h"
#include "intents/topics/vehicle_request_topic.h"

namespace cooboc {
namespace data {
proto::VehicleRequestTopic convert(const intent::VehicleRequestTopic &in) {
    proto::VehicleRequestTopic out;
    for (std::size_t i {0U}; i < 4U; ++i) {
        proto::WheelControlPlanning *wcp = out.add_wheelcontrolplanning();
        *wcp                             = convert(in.wheelControlPlanning[i]);
    }
    return out;
}
}    // namespace data
}    // namespace cooboc