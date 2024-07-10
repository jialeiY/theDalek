#include "hal/i2c.h"
#include <algorithm>
#include "hal/board_def.h"

#ifdef __cplusplus
extern "C" {
#endif

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim5) {
        cooboc::hal::gagaI2C.__IT_onCapture();
    }
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    // LED2_TOGGLE;
}
#ifdef __cplusplus
}
#endif

namespace cooboc {
namespace hal {

void I2C::setup() {
    __it_status_            = OperationStatus::IDLE;
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = 0U;
    __it_readByteOffset_    = 0U;
    __it_readCount_         = 0U;
    __it_transByte_         = 0U;


    // setup clock pin: PE8
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin   = GPIO_PIN_8;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

    // Setup SDA pin: PE7
    GPIO_InitStruct.Pin   = GPIO_PIN_7;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);


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
    //
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    //
    // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);

    // if (__it_status_ == OperationStatus::IDLE) {
    //     return;
    // }

    // if (bitOffset_ < 16U) {
    //     if (bitOffset_ % 2 == 0) {
    //         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
    //     } else {
    //         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
    //     }
    //     bitOffset_++;
    // } else {
    //     __it_status_ = OperationStatus::IDLE;
    // }

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
    __it_transByte_ = __it_writeBuffer_[__it_writeByteOffset_];
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
            if (__it_transByte_ & mask) {
                __IT_sdaUp();
            } else {
                __IT_sdaDown();
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
                bool ack = __IT_sdaRead();
                __IT_clkDown();
                if (ack)
                    LED2_ON;
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
     *  Init status should be sda = 0, clk = 0
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
     *  Quit Status: sda = 0, clk = 0
     */
    const std::size_t bitOffset = __it_operationSequence_ >> 1U;
    const bool isFirstPhase     = (__it_operationSequence_ & 0x01) == 0U;
    if (bitOffset < 8U) {
        if (isFirstPhase) {
            // release sda
            __IT_sdaUp();
            __IT_clkUp();
        } else {
            __it_transByte_ <<= 1U;
            if (__IT_sdaRead()) {
                __it_transByte_ |= 0x01;
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
                __IT_sdaUp();
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

void I2C::__IT_transmitRead() {
    if (__it_readByteOffset_ == 0U) {
        __it_transByte_ = __it_writeBuffer_[0] | 0x01;
        __IT_sendByte();
    } else {
        const bool isNeedAck = (__it_readByteOffset_ < __it_readCount_);
        __IT_receiveByte(isNeedAck);
    }

    if (0U == __it_operationSequence_) {
        if (__it_readByteOffset_ > 0U) {
            dataOut_[__it_readByteOffset_ - 1U] = __it_transByte_;
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
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
}
void I2C::__IT_sdaUp() { HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); }
void I2C::__IT_clkDown() {
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
}
void I2C::__IT_clkUp() { HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); }
bool I2C::__IT_sdaRead() {
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == GPIO_PIN_SET;
}

void I2C::write(const std::uint8_t devAddr,
                const std::uint8_t regAddr,
                const std::uint8_t *data,
                const std::size_t size) {
    __disable_irq();
    if (__it_status_ != OperationStatus::IDLE) {
        __enable_irq();
        return;
    }
    //  Start transmit, setup the state
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = std::min(size + 2U, 4U);
    __it_writeBuffer_[0]    = devAddr << 1U;
    __it_writeBuffer_[1]    = regAddr;
    for (std::size_t i {0U}; i < std::min(size, 4U - 2U); ++i) {
        __it_writeBuffer_[2U + i] = data[i];
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
    __it_writeBuffer_[0]    = devAddr << 1U;
    __it_writeBuffer_[1]    = regAddr;
    __it_readByteOffset_    = 0U;
    __it_readCount_         = std::min(size, 4U);
    __it_status_            = OperationStatus::START;

    __enable_irq();
    return;
}
void I2C::__testTrigger() {
    __disable_irq();
    if (__it_status_ != OperationStatus::IDLE) {
        // I2C in working, quit
        __enable_irq();
        return;
    }

    // // test: write data
    // //  Start transmit, setup the state
    // __it_operationSequence_ = 0U;
    // __it_writeByteOffset_   = 0U;
    // __it_writeCount_        = 2U;
    // __it_writeBuffer_[0]    = 0x36 << 1U;
    // __it_writeBuffer_[1]    = 0x0E;
    // __it_readByteOffset_    = 0U;
    // __it_readCount_         = 0U;
    // __it_status_            = OperationStatus::START;


    // test: read data
    // Start transmit, setup the state
    __it_operationSequence_ = 0U;
    __it_writeByteOffset_   = 0U;
    __it_writeCount_        = 2U;
    __it_writeBuffer_[0]    = 0x36 << 1U;
    __it_writeBuffer_[1]    = 0x0E;
    __it_readByteOffset_    = 0U;
    __it_readCount_         = 2U;
    __it_status_            = OperationStatus::START;


    __enable_irq();
}

I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc
     // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);