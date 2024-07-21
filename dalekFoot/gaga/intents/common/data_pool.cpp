#include "intents/common/data_pool.h"
#include "intents/common/data_defs/encoder_reading_topic.h"
#include "intents/common/data_defs/target_maneuver_topic.h"
#include "intents/common/data_defs/wheel_odometry_topic.h"

namespace cooboc {
namespace data {

EncoderReadingTopic encoderReadingTopic;
WheelOdometryTopic wheelOdometryTopic;
data::TargetManeuverTopic targetManeuverTopic;


}    // namespace data
}    // namespace cooboc