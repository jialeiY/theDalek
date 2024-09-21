#include "intents/debug_data_intent/debug_data_intent.h"
#include "hal/hal.h"
#include "intents/common/data_pool.h"
#include "utils/time.h"

namespace cooboc {
namespace intents {
void DebugDataIntent::setup() {}
void DebugDataIntent::tick() {
    // Print encoder value
    // hal::gagaSerial.println("%d,%d,%d,%d\r\n",
    //                         (int)(data::encoderReadingTopic.encoder[0].value),
    //                         (int)(data::encoderReadingTopic.encoder[1].value),
    //                         (int)(data::encoderReadingTopic.encoder[2].value),
    //                         (int)(data::encoderReadingTopic.encoder[3].value));

    // Print Wheel Speed
    // data::Timepoint now = utils::time::now();
    // data::Timepoint zero;
    // data::Duration d = now - zero;


    // hal::gagaSerial.println("%.3F,%.3F,%.3F,%.3F,%.3F\r\n",
    //                         data::targetManeuverTopic.speed[0],
    //                         data::wheelOdometryTopic.wheelSpeed[0].speed,
    //                         data::wheelOdometryTopic.wheelSpeed[1].speed,
    //                         data::wheelOdometryTopic.wheelSpeed[2].speed,
    //                         data::wheelOdometryTopic.wheelSpeed[3].speed);

    // hal::gagaSerial.println("%d", (zero - now).value());

    const std::uint32_t &tickCounter = data::targetManeuverTopic.tickCount;
    const float &targetSpeed         = data::targetManeuverTopic.speed[3U];
    const float &actualOdometry      = data::wheelOdometryTopic.wheelOdometry[3U].odometry;
    const std::int32_t &sendOdo      = data::vehicleResponseTopic.wheelOdometry[3].odometry;
    hal::gagaSerial.println("%d, %.3F,%.3F,%d", tickCounter, targetSpeed, actualOdometry, sendOdo);
}
}    // namespace intents
}    // namespace cooboc