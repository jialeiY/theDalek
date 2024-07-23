#include "intents/common/data_pool.h"
#include "common/data_defs/encoder_reading_topic.h"
#include "common/data_defs/encoder_reading_trigger_topic.h"
#include "common/data_defs/target_maneuver_topic.h"
#include "common/data_defs/wheel_odometry_topic.h"


namespace cooboc {
namespace data {


EncoderReadingTriggerTopic encoderReadingTriggerTopic;
EncoderReadingTopic encoderReadingTopic;
WheelOdometryTopic wheelOdometryTopic;
data::TargetManeuverTopic targetManeuverTopic;


}    // namespace data
}    // namespace cooboc