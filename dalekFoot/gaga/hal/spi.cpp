#include "hal/spi.h"
#include <data/gh_protocol.h>
#include <cstdint>
#include <cstring>
#include "hal/board_def.h"
#include "stm32f4xx_hal.h"

namespace cooboc {
namespace hal {

struct SpiComm {
    std::int8_t motorPower[4];
} __attribute__((packed));

static std::uint8_t txBuffer[HG_PACKET_SIZE];
static std::uint8_t rxBuffer[HG_PACKET_SIZE];


}    // namespace hal
}    // namespace cooboc

#ifdef __cplusplus
extern "C" {
#endif


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    cooboc::hal::gagaSpi.__onDataReceived();
}

#ifdef __cplusplus
}
#endif

namespace cooboc {
namespace hal {

GagaSpi::GagaSpi() :
    dataReceivedCallback_ {[](const SpiProtocol &) {
    }} {};

void GagaSpi::setup(const OnDataReceivedCallback callback) {
    dataReceivedCallback_ = callback;
    std::memset(txBuffer, 0, sizeof(SpiComm));
    std::memset(rxBuffer, 0, sizeof(SpiComm));
}

void GagaSpi::begin() {
    HAL_SPI_TransmitReceive_DMA(&hspi2, txBuffer, rxBuffer, sizeof(SpiComm));
}

void GagaSpi::__onDataReceived() {
    SpiComm spiComm;
    std::memcpy((void *)&spiComm, rxBuffer, sizeof(SpiComm));

    // Check

    // TODO

    // generate intermediate data
    SpiProtocol spi;
    for (std::size_t i {0U}; i < 4U; ++i) {
        spi.motorPower[i] = spiComm.motorPower[i];
    }

    dataReceivedCallback_(spi);


    HAL_SPI_TransmitReceive_DMA(&hspi2,
                                cooboc::hal::txBuffer,
                                cooboc::hal::rxBuffer,
                                sizeof(cooboc::hal::SpiComm));
}

GagaSpi gagaSpi;

}    // namespace hal
}    // namespace cooboc
