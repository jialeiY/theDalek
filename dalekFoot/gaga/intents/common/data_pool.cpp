#include "intents/common/data_pool.h"
#include "common/data_defs/encoder_reading_topic.h"
#include "common/data_defs/encoder_reading_trigger_topic.h"
#include "common/data_defs/target_maneuver_topic.h"
#include "common/data_defs/vehicle_request_topic.h"
#include "common/data_defs/wheel_odometry_topic.h"

namespace cooboc {
namespace data {


EncoderReadingTriggerTopic encoderReadingTriggerTopic;
EncoderReadingTopic encoderReadingTopic;
WheelOdometryTopic wheelOdometryTopic;
TargetManeuverTopic targetManeuverTopic;
VehicleRequestTopic vehicleRequestTopic;


}    // namespace data
}    // namespace cooboc