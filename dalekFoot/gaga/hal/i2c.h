#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include <cstdint>
#include "hal/board_def.h"

namespace cooboc {
namespace hal {
class I2C {
  public:
    I2C() = default;
    void setup();
    void tick();

    void __onCapture();
    void __testTrigger();

  private:
    bool isWorking_ {false};
    std::size_t bitOffset_ {0U};
};

extern I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc


#endif
