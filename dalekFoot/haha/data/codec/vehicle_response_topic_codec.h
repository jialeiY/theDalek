#ifndef __DATA_CODEC_VEHICLE_RESPONSE_TOPIC_CODEC_H__
#define __DATA_CODEC_VEHICLE_RESPONSE_TOPIC_CODEC_H__


#include "data/defs/vehicle_response.h"
#include "gen/data/proto/vehicle_response_topic.pb.h"
#include "intents/topics/vehicle_response_topic.h"

namespace cooboc {
namespace data {
    proto::WheelStatus convert(const data::WheelStatus & in);

proto::VehicleResponse convert(const data::VehicleResponse &in);


proto::VehicleResponseTopic convert(const intent::VehicleResponseTopic &in);


}    // namespace data
}    // namespace cooboc


#endif
