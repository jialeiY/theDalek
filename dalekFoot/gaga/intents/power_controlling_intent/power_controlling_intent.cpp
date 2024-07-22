#include "intents/power_controlling_intent/power_controlling_intent.h"
#include <array>
#include "hal/hal.h"
#include "intents/common/data_pool.h"
#include "intents/common/parameters.h"
#include "utils/math.h"

class PID {
  public:
    PID() = default;
    void setup() {
        target_        = 0.0F;
        output_        = 0.0F;
        integralError_ = 0.0F;
    }
    void setTarget(float target) { target_ = target; }
    void tick(float current) {
        const float nominalValue = 28.27F * target_ + 110.65;
        // const float kp                  = 40.0f;
        // const float ki                  = 0.1F;
        const float kp    = 30.0F;
        const float ki    = 3.50F;
        const float error = target_ - current;
        integralError_ += error;

        output_ = nominalValue + kp * error + ki * integralError_;
    }
    float getOutput() { return output_; }

  private:
    float target_;
    float output_;
    float integralError_;
};

std::array<PID, 4> pids;


namespace cooboc {
namespace intents {
void PowerControllingIntent::setup() {
    for (auto &p : pids) p.setup();
}
void PowerControllingIntent::tick() {
    for (int i = 0; i < 4; ++i) {
        pids[i].setTarget(data::targetManeuverTopic.speed[i]);
        pids[i].tick(data::wheelOdometryTopic.wheelSpeed[i].speed);
        float output        = pids[i].getOutput();
        output              = parameters::kMotorDirection[i] ? output : -output;
        float clampedOutput = utils::math::clamp(output, -2048.0F, 2048.0F);


        hal::gagaMotors[i].setPower(static_cast<std::int16_t>(clampedOutput));
    }
}
}    // namespace intents
}    // namespace cooboc