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
    void begin();
    void tick();
    bool isBusy();
    void write(const std::uint8_t devAddr,
               const std::uint8_t regAddr,
               const std::uint8_t *data,
               const std::size_t size);
    void read(const std::uint8_t devAddr,
              const std::uint8_t regAddr,
              const std::size_t size);

    void __IT_onCapture();
    void __testTrigger();
    std::uint8_t *__getData() { return dataOut_; };

  private:
    enum class OperationStatus : std::uint8_t {
        IDLE,
        START,
        WRITE,
        READ,
        END,
    };

    OperationStatus __it_status_ {OperationStatus::IDLE};
    std::size_t __it_operationSequence_ {0U};
    // For Write
    std::size_t __it_writeByteOffset_ {0U};
    std::size_t __it_writeCount_ {0U};
    std::uint8_t __it_writeBuffer_[4U] {0U};

    // For Read
    std::size_t __it_readByteOffset_ {0U};
    std::size_t __it_readCount_ {0U};
    std::uint8_t __it_readBuffer_[4U] {0U};

    std::uint8_t __it_transByte_ {0U};

    std::uint8_t dataOut_[4U] {0U};
    // std::size_t byteOffset_ {0U};
    // For debug
    // std::uint8_t transData_[2] {0x36 << 1U, 0x5A};


    inline void __IT_transmitStart();
    inline void __IT_statusTransitStartToReadWriteOrEnd();
    inline void __IT_transmitWrite();
    inline void __IT_transmitRead();
    inline void __IT_transmitEnd();


    inline void __IT_sendByte();
    inline void __IT_receiveByte(bool ack);
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
