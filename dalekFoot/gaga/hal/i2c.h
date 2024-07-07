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

    void __IT_onCapture();
    void __testTrigger();

  private:
    enum class OperationStatus : std::uint8_t {
        IDLE,
        START,
        WRITE,
        END,
    };

    OperationStatus status_ {OperationStatus::IDLE};
    std::size_t operationSequence_ {0U};
    // std::size_t byteOffset_ {0U};
    // For debug
    std::uint8_t transData_[2] {0x36 << 1U, 0x5A};


    inline void __IT_transmitStart();
    inline void __IT_transmitWrite();
    inline void __IT_transmitEnd();
    inline void __IT_sendByte();
    inline void __IT_sdaDown();
    inline void __IT_sdaUp();
    inline void __IT_clkDown();
    inline void __IT_clkUp();
    inline bool __IT_sdaRead();
};

extern I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc


#endif
