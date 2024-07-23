#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include <array>
#include <cstdint>
#include "hal/board_def.h"

namespace cooboc {
namespace hal {

namespace detail {
constexpr std::size_t WRITE_BUFFER_SIZE {4U};
constexpr std::size_t OUTPUT_BUFFER_SIZE {4U};
constexpr std::size_t PORT_NUMBER {4U};

class I2CPort {
  public:
    I2CPort() = default;
    void setup(GPIO_TypeDef *const clkPort,
               const std::uint16_t clkPin,
               GPIO_TypeDef *const sdaPort,
               const std::uint16_t sdaPin);
    void sdaDown();
    void sdaUp();
    void clkDown();
    void clkUp();
    bool readSda();


    inline std::uint8_t getTransByte() { return transByte_; }
    inline void setTransByte(std::uint8_t byte) { transByte_ = byte; }
    inline std::uint8_t *getWriteBufferPtr() { return writeBuffer_; }
    inline void pushBitToTransByte(bool status);
    inline std::uint8_t *getOutputBufferPtr() { return outputBuffer_; }

  private:
    GPIO_TypeDef *clkPort_;
    std::uint16_t clkPin_;
    GPIO_TypeDef *sdaPort_;
    std::uint16_t sdaPin_;

    void initHardware();

    std::uint8_t transByte_;
    std::uint8_t writeBuffer_[WRITE_BUFFER_SIZE];
    std::uint8_t outputBuffer_[OUTPUT_BUFFER_SIZE];
};
}    // namespace detail

class I2C {
  public:
    using PortsType = std::array<detail::I2CPort, detail::PORT_NUMBER>;
    struct I2CResult {
        std::uint8_t *dataBufferPtr {0U};
        std::uint8_t *dataHealth {0U};
    };
    I2C() = default;
    void setup();
    void begin();
    void tick();
    bool isBusy();
    void write(const std::uint8_t devAddr,
               const std::uint8_t regAddr,
               const std::uint8_t *data,
               const std::size_t size);
    bool read(const std::uint8_t devAddr,
              const std::uint8_t regAddr,
              const std::size_t size);

    void __IT_onCapture();


    // void __testTrigger();
    // std::uint8_t *__getData() { return dataOut_; };
    std::array<I2CResult, detail::PORT_NUMBER> getData();


  private:
    enum class OperationStatus : std::uint8_t {
        IDLE,
        START,
        WRITE,
        READ,
        END,
    };

    PortsType ports_;

    OperationStatus __it_status_ {OperationStatus::IDLE};
    std::size_t __it_operationSequence_ {0U};
    // For Write
    std::size_t __it_writeByteOffset_ {0U};
    std::size_t __it_writeCount_ {0U};

    // For Read
    std::size_t __it_readByteOffset_ {0U};
    std::size_t __it_readCount_ {0U};

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
};

extern I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc


#endif
