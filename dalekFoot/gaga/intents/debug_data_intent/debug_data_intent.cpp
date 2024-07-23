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


    hal::gagaSerial.println("%.2F,%.2F,%.2F,%.2F\r\n",
                            data::wheelOdometryTopic.wheelSpeed[0].speed,
                            data::wheelOdometryTopic.wheelSpeed[1].speed,
                            data::wheelOdometryTopic.wheelSpeed[2].speed,
                            data::wheelOdometryTopic.wheelSpeed[3].speed);

    // hal::gagaSerial.println("%d", (zero - now).value());
}
}    // namespace intents
}    // namespace cooboc