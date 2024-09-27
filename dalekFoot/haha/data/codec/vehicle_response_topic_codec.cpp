#include <cstdint>
#include "data/defs/vehicle_response.h"
#include "gen/data/proto/vehicle_response_topic.pb.h"
#include "intents/topics/vehicle_response_topic.h"

namespace cooboc {
namespace data {

proto::VehicleResponseTopic convert(const intent::VehicleResponseTopic &in) {
    proto::VehicleResponseTopic out;
    out.set_isvalid(in.isValid);
    for (std::size_t i {0U}; i < 4U; ++i) {
        out.add_encoderodometry(in.encoderOdometry[i]);
        out.add_encoderspeed(in.encoderSpeed[i]);
    }
    return out;
}
}    // namespace data
}    // namespace cooboc