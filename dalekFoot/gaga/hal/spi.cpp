#include "hal/spi.h"
#include <data/gh_protocol.h>
#include <cstdint>
#include <cstring>
#include "hal/board_def.h"
#include "stm32f4xx_hal.h"

namespace cooboc {
namespace hal {

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
    dataReceivedCallback_ {[](const comm::HGPacket &) {
    }} {};

void GagaSpi::setup(const OnDataReceivedCallback callback) {
    dataReceivedCallback_ = callback;
    std::memset(txBuffer, 0, HG_PACKET_SIZE);
    std::memset(rxBuffer, 0, HG_PACKET_SIZE);
    std::memset(&spiBuffer_, 0, HG_PACKET_SIZE);
}

void GagaSpi::begin() {
    HAL_SPI_TransmitReceive_DMA(&hspi2, txBuffer, rxBuffer, HG_PACKET_SIZE);
}

void GagaSpi::__onDataReceived() {
    // Copy data to local memory immediately
    std::memcpy((void *)&spiBuffer_, rxBuffer, HG_PACKET_SIZE);

    dataReceivedCallback_(spiBuffer_);


    HAL_SPI_TransmitReceive_DMA(
      &hspi2, cooboc::hal::txBuffer, cooboc::hal::rxBuffer, HG_PACKET_SIZE);
}

GagaSpi gagaSpi;

}    // namespace hal
}    // namespace cooboc
