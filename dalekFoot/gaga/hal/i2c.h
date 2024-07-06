#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include "hal/board_def.h"

namespace cooboc {
namespace hal {
class I2C {
  public:
    I2C() = default;
    void setup();
    void tick();

    void __onCapture();

  private:
    bool isWorknig_ {false};
};

extern I2C gagaI2c;

}    // namespace hal
}    // namespace cooboc


#endif
