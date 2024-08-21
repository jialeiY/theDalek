#ifndef __DATA_CODEC_VEHICLE_REQUEST_TOPIC_CODEC_H__
#define __DATA_CODEC_VEHICLE_REQUEST_TOPIC_CODEC_H__

#include "gen/data/proto/vehicle_request_topic.pb.h"
#include "intents/topics/vehicle_request_topic.h"

namespace cooboc {
namespace data {

proto::VehicleRequestTopic convert(const intent::VehicleRequestTopic &);

}    // namespace data
}    // namespace cooboc

#endif
