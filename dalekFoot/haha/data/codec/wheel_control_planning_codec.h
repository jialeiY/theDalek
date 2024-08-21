#ifndef __DATA_CODEC_WHEEL_CONTROL_PLANNING_CODEC_H__
#define __DATA_CODEC_WHEEL_CONTROL_PLANNING_CODEC_H__

#include "gen/data/proto/wheel_control_planning.pb.h"
#include "intents/topics/vehicle_request_topic.h"

namespace cooboc {
namespace data {


proto::WheelControlPlanning convert(const intent::WheelControlPlanning &);

}    // namespace data
}    // namespace cooboc

#endif
