#include "hal/i2c.h"
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
    __it_task_              = Task::IDLE;
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
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

    // Setup SDA pin: PE7
    GPIO_InitStruct.Pin   = GPIO_PIN_7;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
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
            __it_operationSequence_++;
            break;
        }
        default: {
            __IT_clkDown();
            __IT_statusTransitStartToReadWriteOrEnd();
            break;
        }
    }
}

void I2C::__IT_statusTransitStartToReadWriteOrEnd() {
    __it_operationSequence_ = 0U;
    if (__it_writeByteOffset_ < __it_writeCount_) {
        __it_status_ = OperationStatus::WRITE;
    } else {
        if (__it_readByteOffset_ < (__it_readCount_ + 1U)) {
            __it_transByte_ = 0U;
            __it_status_    = OperationStatus::READ;
        } else {
            __it_status_ = OperationStatus::END;
        }
    }
}

void I2C::__IT_transmitWrite() {
    const std::size_t bitOffset = __it_operationSequence_ >> 1U;
    const bool isFirstPhase     = (__it_operationSequence_ & 0x01) == 0U;

    if (bitOffset < 8U) {
        // Send Data
        __it_transByte_ = __it_writeBuffer_[__it_writeByteOffset_];
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
        __it_operationSequence_++;
    } else {
        // request ack
        if (isFirstPhase) {
            __IT_clkDown();
            __it_operationSequence_++;
            __IT_sdaUp();
        } else {
            __IT_clkUp();
            // TODO
            if (__IT_sdaRead()) {
                LED2_ON;
            }
            __it_operationSequence_ = 0U;
            __it_writeByteOffset_++;
            if (__it_writeByteOffset_ >= __it_writeCount_) {
                __it_status_ = OperationStatus::END;
            }
        }
    }
}
void I2C::__IT_transmitRead() {
    // __it_readByteOffset_    = __it_readCount_ + 1U;
    // __it_operationSequence_ = 0U;
    // __it_status_            = OperationStatus::END;
    const std::size_t bitOffset = __it_operationSequence_ >> 1U;
    const bool isFirstPhase     = (__it_operationSequence_ & 0x01) == 0U;
    if (0U == __it_readByteOffset_) {
        if (bitOffset < 8U) {
            // Write device Addr
            __it_transByte_ = __it_writeBuffer_[0] | 0x01;
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
            __it_operationSequence_++;
        } else {
            // request ack
            if (isFirstPhase) {
                __IT_clkDown();
                __it_operationSequence_++;
                __IT_sdaUp();
            } else {
                __IT_clkUp();
                // TODO
                if (__IT_sdaRead()) {
                    LED2_ON;
                }
                __it_operationSequence_ = 0U;
                __it_transByte_         = 0U;
                __it_readByteOffset_++;
            }
        }
    } else {
        // read data
        if (bitOffset < 8U) {
            // Read Data
            if (isFirstPhase) {
                __IT_clkDown();
                // Release SDA
                __IT_sdaUp();
            } else {
                __IT_clkUp();
                __it_transByte_ <<= 1U;
                if (__IT_sdaRead()) {
                    __it_transByte_ |= 0x01;
                }
                dataOut_[__it_readByteOffset_ - 1U] = __it_transByte_;
            }
            __it_operationSequence_++;
        } else {
            // Generate ACK
            if (isFirstPhase) {
                LED2_ON;
                __IT_clkDown();
                if (__it_readByteOffset_ < __it_readCount_) {
                    // Not last byte
                    __IT_sdaDown();
                } else {
                    __IT_sdaUp();
                }
                __it_operationSequence_++;
            } else {
                // Release SDA
                __IT_sdaUp();
                LED2_OFF;
                __IT_clkUp();
                __it_operationSequence_ = 0U;
                __it_readByteOffset_++;
                if (__it_readByteOffset_ > __it_readCount_) {
                    __it_status_ = OperationStatus::END;
                }
            }
        }
        // __it_readByteOffset_ = __it_readCount_ + 1;
        // __it_status_         = OperationStatus::END;
    }
}

void I2C::__IT_transmitEnd() {
    switch (__it_operationSequence_) {
        case (0U): {
            __IT_clkDown();
            __IT_sdaDown();
            __it_operationSequence_++;
            break;
        }
        case (1U): {
            __IT_clkUp();
            __it_operationSequence_++;
            break;
        }
        default: {
            __IT_sdaUp();
            __it_operationSequence_ = 0U;
            // TODO, check if need to repeat start

            if (__it_task_ == Task::WRITE) {
                // Only one frame, just end it
                __it_status_ = OperationStatus::IDLE;
            } else {
                // Must be Task::READ
                if (__it_readByteOffset_ < __it_readCount_) {
                    __it_status_ = OperationStatus::START;
                } else {
                    __it_status_ = OperationStatus::IDLE;
                }
            }
            break;
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
void I2C::__testTrigger() {
    __disable_irq();
    if (__it_status_ != OperationStatus::IDLE) {
        // I2C in working, quit
        __enable_irq();
        return;
    }

    // // test: write data
    // //  Start transmit, setup the state
    // __it_task_              = Task::WRITE;
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
    __it_task_              = Task::READ;
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