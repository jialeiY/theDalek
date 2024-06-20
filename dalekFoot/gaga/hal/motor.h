#ifndef __HAL_MOTOR_H__
#define __HAL_MOTOR_H__

namespace cooboc {
namespace hal {

class Motor {
  public:
    Motor();
    void setup();
    void tick();
};


extern Motor motor;
}    // namespace hal
}    // namespace cooboc
#endif
