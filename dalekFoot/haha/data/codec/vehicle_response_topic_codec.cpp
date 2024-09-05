#include <cstdint>
#include "data/defs/vehicle_response.h"
#include "gen/data/proto/vehicle_response_topic.pb.h"
#include "intents/topics/vehicle_response_topic.h"

namespace cooboc {
namespace data {

proto::WheelStatus convert(const data::WheelStatus &in) {
    proto::WheelStatus out;
    out.set_encoder(in.encoder);
    out.set_speed(in.speed);
    out.set_odometry(in.odometry);
    return out;
}

proto::VehicleResponse convert(const data::VehicleResponse &in) {
    proto::VehicleResponse out;

    for (std::size_t i {0U}; i < 4U; ++i) {
        proto::WheelStatus *ws = out.add_wheelstatus();
        *ws                    = convert(in.wheelStatus[i]);
    }
    return out;
}

proto::VehicleResponseTopic convert(const intent::VehicleResponseTopic &in) {
    proto::VehicleResponseTopic out;
    proto::VehicleResponse *resp = out.mutable_response();
    *resp                        = convert(in.response);

    return out;
}
}    // namespace data
}    // namespace cooboc