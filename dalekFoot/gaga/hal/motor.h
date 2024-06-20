#ifndef __HAL_MOTOR_H__
#define __HAL_MOTOR_H__

#include <cstdint>

namespace cooboc {
namespace hal {

class Motor {
  public:
    Motor();
    void setup();
    void tick();
    void setPower(std::int16_t value);
};


extern Motor motor;
}    // namespace hal
}    // namespace cooboc
#endif
