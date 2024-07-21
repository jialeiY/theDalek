#include "hal/driver/i2c.h"
#include <algorithm>
#include <cstring>
#include "hal/board_def.h"

namespace cooboc {
namespace hal {

namespace detail {

void I2CPort::setup(GPIO_TypeDef *const clkPort,
                    const std::uint16_t clkPin,
                    GPIO_TypeDef *const sdaPort,
                    const std::uint16_t sdaPin) {
    clkPort_ = clkPort;
    clkPin_  = clkPin;
    sdaPort_ = sdaPort;
    sdaPin_  = sdaPin;

    transByte_ = 0U;
    std::memset(writeBuffer_, 0U, WRITE_BUFFER_SIZE);

    initHardware();
}


void I2CPort::initHardware() {
    // setup clock pin
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin   = clkPin_;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(clkPort_, &GPIO_InitStruct);
    HAL_GPIO_WritePin(clkPort_, clkPin_, GPIO_PIN_SET);

    // Setup SDA pin
    GPIO_InitStruct.Pin   = sdaPin_;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(sdaPort_, &GPIO_InitStruct);
    HAL_GPIO_WritePin(sdaPort_, sdaPin_, GPIO_PIN_SET);
}


void I2CPort::clkDown() {
    //
    HAL_GPIO_WritePin(clkPort_, clkPin_, GPIO_PIN_RESET);
}
void I2CPort::clkUp() {
    //
    HAL_GPIO_WritePin(clkPort_, clkPin_, GPIO_PIN_SET);
}
void I2CPort::sdaDown() {
    //
    HAL_GPIO_WritePin(sdaPort_, sdaPin_, GPIO_PIN_RESET);
}
void I2CPort::sdaUp() {
    //
    HAL_GPIO_WritePin(sdaPort_, sdaPin_, GPIO_PIN_SET);
}
bool I2CPort::readSda() {
    //
    return HAL_GPIO_ReadPin(sdaPort_, sdaPin_) == GPIO_PIN_SET;
}

void I2CPort::pushBitToTransByte(bool status) {
    transByte_ <<= 1U;
    if (status) {
        transByte_ |= 0x01;
    }
}

}    // namespace detail

void I2C::setup() {
    // Hardware initialization
    // setup clock pin: PE8
    // Setup SDA pin: PE7
    ports_[0U].setup(GPIOE, GPIO_PIN_8, GPIOE, GPIO_PIN_7);
    ports_[1U].setup(GPIOE, GPIO_PIN_6, GPIOE, GPIO_PIN_5);
    ports_[2U].setup(GPIOC, GPIO_PIN_9, GPIOA, GPIO_PIN_8);
    ports_[3U].setup(GPIOB, GPIO_PIN_11, GPIOB, GPIO_PIN_10);

    __it_status_            = OperationStatus::IDLE;
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = 0U;
    __it_readByteOffset_    = 0U;
    __it_readCount_         = 0U;
}

void I2C::begin() {
    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim5);
}

void I2C::tick() {}
bool I2C::isBusy() {
    __disable_irq();
    const OperationStatus status = __it_status_;
    __enable_irq();
    return status != OperationStatus::IDLE;
}

void I2C::__IT_onCapture() {
    switch (__it_status_) {
        case (OperationStatus::IDLE): {
            // DO nothing
            return;
        }
        case (OperationStatus::START): {
            __IT_transmitStart();
            break;
        }
        case (OperationStatus::WRITE): {
            __IT_transmitWrite();
            break;
        }
        case (OperationStatus::READ): {
            __IT_transmitRead();
            break;
        }
        case (OperationStatus::END): {
            __IT_transmitEnd();
            break;
        }
        default: {
            // ERROR
            break;
        }
    }
}

void I2C::__IT_transmitStart() {
    switch (__it_operationSequence_) {
        case (0U): {
            __IT_sdaDown();
            break;
        }
        default: {
            __IT_clkDown();
            // start must followed by write device addr
            __it_operationSequence_ = 0U;
            if (__it_writeByteOffset_ < __it_writeCount_) {
                __it_status_ = OperationStatus::WRITE;
            } else {
                if (__it_readCount_ > 0U) {
                    __it_status_ = OperationStatus::READ;
                } else {
                    __it_status_ = OperationStatus::END;
                }
            }
            return;
        }
    }
    __it_operationSequence_++;
}

void I2C::__IT_statusTransitStartToReadWriteOrEnd() {
    __it_operationSequence_ = 0U;
    if (__it_writeByteOffset_ < __it_writeCount_) {
        __it_status_ = OperationStatus::WRITE;
    } else {
        if (__it_readByteOffset_ < (__it_readCount_ + 1U)) {
            __it_status_ = OperationStatus::READ;
        } else {
            __it_status_ = OperationStatus::END;
        }
    }
}

void I2C::__IT_transmitWrite() {
    for (std::size_t i {0U}; i < ports_.size(); ++i) {
        ports_[i].setTransByte(
          (ports_[i].getWriteBufferPtr())[__it_writeByteOffset_]);
    }

    __IT_sendByte();
    if (0U == __it_operationSequence_) {
        // Send byte finished
        __it_writeByteOffset_++;
        if (__it_writeByteOffset_ >= __it_writeCount_) {
            __it_status_ = OperationStatus::END;
        }
    }
}

void I2C::__IT_sendByte() {
    /**
     *  Init status should be sda = 0, clk = 0
     *
     *  0 clk down and change data for bit 1
     *  1 clk up for bit 1
     *  ...
     *  14 for bit 8
     *  15 for bit 8
     *  16 clk down and release sda
     *  17 clk up and read sda
     *  18 clk down
     *  19 sda down
     *
     *  Quit status should be sda = 0, clk = 0
     */
    const std::size_t bitOffset = __it_operationSequence_ >> 1U;
    const bool isFirstPhase     = (__it_operationSequence_ & 0x01) == 0U;

    if (bitOffset < 8U) {
        // Send Data
        if (isFirstPhase) {
            __IT_clkDown();
            // Send MSB first
            const std::uint8_t mask = 0x01 << (7U - bitOffset);
            for (std::size_t i {0U}; i < ports_.size(); ++i) {
                if (ports_[i].getTransByte() & mask) {
                    ports_[i].sdaUp();
                } else {
                    ports_[i].sdaDown();
                }
            }
        } else {
            __IT_clkUp();
        }
    } else {
        switch (__it_operationSequence_) {
            case (16): {
                // clock down for bit 8 and release sda for request ack
                __IT_clkDown();
                __IT_sdaUp();
                break;
            }
            case (17): {
                __IT_clkUp();
                break;
            }
            case (18): {
                // read ack and clk down
                // TODO:
                // bool ack = __IT_sdaRead();
                __IT_clkDown();
                // if (ack)
                // LED2_ON;
                break;
            }
            default: {
                __IT_sdaDown();
                __it_operationSequence_ = 0U;
                return;
            }
        }
    }
    ++__it_operationSequence_;
}

void I2C::__IT_receiveByte(bool ack) {
    /**
     *  Init status should be sda = X, clk = 0
     *
     *  0 clk up for bit 1
     *  1 read and clock down for bit 1
     *  ...
     *  14 for bit 8
     *  15 for bit 8
     *  16 ack
     *  17 ack clock up
     *  18 ack clock down, release sda
     *  19 release sda
     *  Quit Status: sda = 1, clk = 0
     */
    const std::size_t bitOffset = __it_operationSequence_ >> 1U;
    const bool isFirstPhase     = (__it_operationSequence_ & 0x01) == 0U;
    if (bitOffset < 8U) {
        if (isFirstPhase) {
            // release sda
            __IT_sdaUp();
            __IT_clkUp();
        } else {
            for (std::size_t i {0U}; i < ports_.size(); ++i) {
                ports_[i].pushBitToTransByte(ports_[i].readSda());
            }
            __IT_clkDown();
        }
    } else {
        switch (__it_operationSequence_) {
            case (16): {
                if (ack) {
                    __IT_sdaDown();

                } else {
                    __IT_sdaUp();
                }
                break;
            }
            case (17): {
                // clock up for ack
                __IT_clkUp();
                break;
            }
            case (18): {
                // clock down for ack and release
                __IT_clkDown();
                break;
            }
            default: {
                __IT_sdaUp();
                __it_operationSequence_ = 0U;
                return;
            }
        }
    }
    ++__it_operationSequence_;
}

void I2C::__IT_transmitRead() {
    if (__it_readByteOffset_ == 0U) {
        // Generate read address
        for (std::size_t i {0U}; i < ports_.size(); ++i) {
            ports_[i].setTransByte(ports_[i].getWriteBufferPtr()[0U] | 0x01);
        }
        __IT_sendByte();
    } else {
        const bool isNeedAck = (__it_readByteOffset_ < __it_readCount_);
        __IT_receiveByte(isNeedAck);
    }

    if (0U == __it_operationSequence_) {
        if (__it_readByteOffset_ > 0U) {
            for (std::size_t i {0U}; i < ports_.size(); ++i) {
                ports_[i].getOutputBufferPtr()[__it_readByteOffset_ - 1U] =
                  ports_[i].getTransByte();
            }
        }
        __it_readByteOffset_++;
        if (__it_readByteOffset_ > __it_readCount_) {
            __it_status_ = OperationStatus::END;
        }
    }
}

void I2C::__IT_transmitEnd() {
    /**
     * Init status: clk = 0, sda = 0
     *  0, clk up
     *  1, sda up
     *
     * Quit status: clk = 1, sda = 1
     *
     *
     */
    switch (__it_operationSequence_) {
        case (0U): {
            __IT_clkUp();
            __it_operationSequence_++;
            break;
        }
        default: {
            __IT_sdaUp();
            __it_operationSequence_ = 0U;
            if (__it_readCount_ > 0) {    // Read task
                if (__it_readByteOffset_ > __it_readCount_) {
                    __it_status_ = OperationStatus::IDLE;
                } else {
                    __it_status_ = OperationStatus::START;
                }
            } else {
                // write task
                __it_status_ = OperationStatus::IDLE;
            }
            return;
        }
    }
}

void I2C::__IT_sdaDown() {
    for (auto &p : ports_) { p.sdaDown(); }
}
void I2C::__IT_sdaUp() {
    for (auto &p : ports_) { p.sdaUp(); }
}
void I2C::__IT_clkDown() {
    for (auto &p : ports_) { p.clkDown(); }
}
void I2C::__IT_clkUp() {
    for (auto &p : ports_) { p.clkUp(); }
}
// bool I2C::__IT_sdaRead() { return ports_[0U].readSda(); }

void I2C::write(const std::uint8_t devAddr,
                const std::uint8_t regAddr,
                const std::uint8_t *data,
                const std::size_t size) {
    // TODO: is it necessary to disable interrupt for such long time?
    __disable_irq();
    if (__it_status_ != OperationStatus::IDLE) {
        __enable_irq();
        return;
    }
    //  Start transmit, setup the state
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = std::min(size + 2U, 4U);
    for (std::size_t i {0U}; i < ports_.size(); ++i) {
        std::uint8_t *portWriteBuffer = ports_[i].getWriteBufferPtr();
        portWriteBuffer[0]            = devAddr << 1U;
        portWriteBuffer[1]            = regAddr;

        // Copy data to write_buffer
        static_assert(detail::WRITE_BUFFER_SIZE > 2U);
        for (std::size_t j {0U};
             j < std::min(size, detail::WRITE_BUFFER_SIZE - 2U);
             ++j) {
            portWriteBuffer[2U + i] = data[i];
        }
    }

    // Nothing for read
    __it_readByteOffset_ = 0U;
    __it_readCount_      = 0U;

    __it_status_ = OperationStatus::START;
    __enable_irq();
    return;
}


void I2C::read(const std::uint8_t devAddr,
               const std::uint8_t regAddr,
               const std::size_t size) {
    __disable_irq();
    if (__it_status_ != OperationStatus::IDLE) {
        __enable_irq();
        return;
    }
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = 2U;
    for (std::size_t i {0U}; i < ports_.size(); ++i) {
        std::uint8_t *portWriteBuffer = ports_[i].getWriteBufferPtr();
        portWriteBuffer[0]            = devAddr << 1U;
        portWriteBuffer[1]            = regAddr;
    }
    __it_readByteOffset_ = 0U;
    __it_readCount_      = std::min(size, 4U);
    __it_status_         = OperationStatus::START;

    __enable_irq();
    return;
}

std::array<I2C::I2CResult, detail::PORT_NUMBER> I2C::getData() {
    std::array<I2CResult, detail::PORT_NUMBER> ret;

    // TODO
    for (std::size_t i {0U}; i < detail::PORT_NUMBER; ++i) {
        ret[i].dataBufferPtr = ports_[i].getOutputBufferPtr();
        ret[i].dataHealth    = 0x00;
    }

    return ret;
}

// void I2C::__testTrigger() {
//     __disable_irq();
//     if (__it_status_ != OperationStatus::IDLE) {
//         // I2C in working, quit
//         __enable_irq();
//         return;
//     }

//     // // test: write data
//     // //  Start transmit, setup the state
//     // __it_operationSequence_ = 0U;
//     // __it_writeByteOffset_   = 0U;
//     // __it_writeCount_        = 2U;
//     // __it_writeBuffer_[0]    = 0x36 << 1U;
//     // __it_writeBuffer_[1]    = 0x0E;
//     // __it_readByteOffset_    = 0U;
//     // __it_readCount_         = 0U;
//     // __it_status_            = OperationStatus::START;


//     // test: read data
//     // Start transmit, setup the state
//     __it_operationSequence_ = 0U;
//     __it_writeByteOffset_   = 0U;
//     __it_writeCount_        = 2U;
//     __it_writeBuffer_[0]    = 0x36 << 1U;
//     __it_writeBuffer_[1]    = 0x0E;
//     __it_readByteOffset_    = 0U;
//     __it_readCount_         = 2U;
//     __it_status_            = OperationStatus::START;


//     __enable_irq();
// }

I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc
     // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);