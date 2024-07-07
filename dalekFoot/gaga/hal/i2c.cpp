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
    status_            = OperationStatus::IDLE;
    operationSequence_ = 0U;
    transData_[0]      = 0x36 << 1U;
    // byteOffset_        = 0U;

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

void I2C::__IT_onCapture() {
    //
    // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    //
    // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);

    // if (status_ == OperationStatus::IDLE) {
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
    //     status_ = OperationStatus::IDLE;
    // }

    switch (status_) {
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
    switch (operationSequence_) {
        case (0U): {
            __IT_sdaDown();
            operationSequence_++;
            break;
        }
        default: {
            __IT_clkDown();
            operationSequence_ = 0U;
            // byteOffset_        = 0U;
            status_ = OperationStatus::WRITE;
            break;
        }
    }
}

inline void I2C::__IT_transmitWrite() {
    const std::size_t bitOffset = operationSequence_ >> 1U;
    const bool isFirstPhase     = (operationSequence_ & 0x01) == 0U;

    if (bitOffset < 8U) {
        // Send Data
        if (isFirstPhase) {
            __IT_clkDown();
            // Send MSB first
            const std::uint8_t mask = 0x01 << (7U - bitOffset);
            if (transData_[0] & mask) {
                __IT_sdaUp();
            } else {
                __IT_sdaDown();
            }
        } else {
            __IT_clkUp();
        }
        operationSequence_++;
    } else {
        // request ack
        if (isFirstPhase) {
            __IT_clkDown();
            operationSequence_++;
            __IT_sdaUp();
            // TODO: change SDA to read
        } else {
            __IT_clkUp();
            if (__IT_sdaRead()) {
                LED2_ON;
            }

            operationSequence_ = 0U;
            status_            = OperationStatus::END;
        }
    }
}

void I2C::__IT_transmitEnd() {
    switch (operationSequence_) {
        case (0U): {
            __IT_clkDown();
            __IT_sdaDown();
            operationSequence_++;
            break;
        }
        case (1U): {
            __IT_clkUp();
            operationSequence_++;
            break;
        }
        default: {
            __IT_sdaUp();
            operationSequence_ = 0U;
            // TODO, check if need to repeat start
            status_ = OperationStatus::IDLE;
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
    if (status_ != OperationStatus::IDLE) {
        // I2C in working, quit
        __enable_irq();
        return;
    }

    // Start transmit, setup the state
    operationSequence_ = {0U};
    status_            = OperationStatus::START;
    __enable_irq();
}

I2C gagaI2C;

}    // namespace hal
}    // namespace cooboc
     // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);