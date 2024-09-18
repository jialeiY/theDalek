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
        previousError_ = 0.0F;
    }
    void setTarget(float target) { target_ = target; }
    void tick(float current) {
        // Parameter for controlling based on encoder value
        // const float feedForward = (28.27F * target_) * 652 + 110.65;
        // const float kp          = 40.0f;
        // const float ki          = 0.1F;
        // const float kp          = 30.0F / 652;
        // const float ki          = 3.50F / 652;


        const float feedForward = (30.27F * target_) + 110.65;
        const float kp          = 30.0F;
        const float ki          = 0.2F;
        const float kd          = 30.0F;


        // Parameter for controlling based on real odometry
        // const float feedForward = target_ * 1240.0F + 110.65;
        // const float kp           = 1290.0F;
        // const float ki           = 150.0F;
        // const float kd           = 1500.0F;


        const float error = target_ - current;
        integralError_ += error;

        output_ = feedForward + (kp * error) + (ki * integralError_) +
                  (kd * (error - previousError_));
        previousError_ = error;
    }
    float getOutput() { return output_; }

  private:
    float target_ {0.0F};
    float output_ {0.0F};
    float integralError_ {0.0F};
    float previousError_ {0.0F};
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