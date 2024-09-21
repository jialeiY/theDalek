#include "hal/spi.h"
#include <data/gh_protocol.h>
#include <cstdint>
#include <cstring>
#include "hal/board_def.h"
#include "stm32f4xx_hal.h"

namespace cooboc {
namespace hal {

static std::uint8_t spiTxDmaBuffer[HG_PROTOCOL_SIZE];
static std::uint8_t spiRxDmaBuffer[HG_PROTOCOL_SIZE];


}    // namespace hal
}    // namespace cooboc

#ifdef __cplusplus
extern "C" {
#endif


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) { cooboc::hal::gagaSpi.__onDataReceived(); }

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
    std::memset(spiTxDmaBuffer, 0, HG_PROTOCOL_SIZE);
    std::memset(spiRxDmaBuffer, 0, HG_PROTOCOL_SIZE);
    std::memset(&localRxBuffer_, 0, HG_PACKET_SIZE);
    std::memset(&localTxBuffer_, 0, GH_PACKET_SIZE);
}

void GagaSpi::begin() {
    HAL_SPI_TransmitReceive_DMA(&hspi2, spiTxDmaBuffer, spiRxDmaBuffer, HG_PROTOCOL_SIZE);
}

void GagaSpi::__onDataReceived() {
    // Copy data to local memory immediately
    std::memcpy((void *)&localRxBuffer_, spiRxDmaBuffer, HG_PACKET_SIZE);

    // Copy send data to dma
    std::memcpy(spiTxDmaBuffer, (const void *)(&localTxBuffer_), GH_PACKET_SIZE);

    dataReceivedCallback_(localRxBuffer_);

    HAL_SPI_TransmitReceive_DMA(
      &hspi2, cooboc::hal::spiTxDmaBuffer, cooboc::hal::spiRxDmaBuffer, HG_PROTOCOL_SIZE);
}

GagaSpi gagaSpi;

}    // namespace hal
}    // namespace cooboc
