#ifndef __COMMON_DATA_POOL_H__
#define __COMMON_DATA_POOL_H__

#include "common/data_defs/encoder_reading_topic.h"
#include "common/data_defs/encoder_reading_trigger_topic.h"
#include "common/data_defs/target_maneuver_topic.h"
#include "common/data_defs/vehicle_request_topic.h"
#include "common/data_defs/vehicle_response_topic.h"
#include "common/data_defs/wheel_odometry_topic.h"


namespace cooboc {
namespace data {

/**
 * Output: SPI interrupter
 * Input: all
 */
extern VehicleRequestTopic vehicleRequestTopic;


/**
 * Output:  EncoderReadingTriggerIntent
 * Input:   EncoderReadingIntent
 */
extern EncoderReadingTriggerTopic encoderReadingTriggerTopic;

/**
 * Output:  EncoderReadingIntent
 * Input:   DebugDataIntent
 *          -- Next Cycle --
 *          WheelOdometryIntent
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

/**
 * Output: VehicleResponseIntent
 * Input: --
 */
extern data::VehicleResponseTopic vehicleResponseTopic;

}    // namespace data
}    // namespace cooboc

#endif
