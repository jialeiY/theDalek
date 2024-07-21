#ifndef __INTENTS_COMMON_DATA_POOL_H__
#define __INTENTS_COMMON_DATA_POOL_H__

#include "intents/common/data_defs/encoder_reading_topic.h"
#include "intents/common/data_defs/target_maneuver_topic.h"
#include "intents/common/data_defs/wheel_odometry_topic.h"

namespace cooboc {
namespace data {


/**
 * Output:  EncoderReadingIntent
 * Input:   DebugDataIntent
 *          -- Next Cycle --
 *          WheelodometryIntent
 *
 */

extern data::EncoderReadingTopic encoderReadingTopic;


/**
 * Output:  WheelOdometryIntent
 * Input:   PowerControllingIntent
 */
extern data::WheelOdometryTopic wheelOdometryTopic;


/**
 * Output:  TargetManeuverIntent
 * Input:   PowerControllingIntent
 */
extern data::TargetManeuverTopic targetManeuverTopic;

}    // namespace data
}    // namespace cooboc

#endif
