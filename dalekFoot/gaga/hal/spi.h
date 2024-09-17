#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include <data/gh_protocol.h>
#include <cstdint>
#include <functional>

namespace cooboc {
namespace hal {


class GagaSpi {
    using OnDataReceivedCallback = std::function<void(const comm::HGPacket &)>;

  public:
    GagaSpi();
    void setup(const OnDataReceivedCallback callback);
    void tick();
    void begin();

    inline void __onDataReceived();
    inline const comm::HGPacket &getSpiPacketRef() { return spiBuffer_; }

  private:
    OnDataReceivedCallback dataReceivedCallback_;
    comm::HGPacket spiBuffer_;
};

extern GagaSpi gagaSpi;

}    // namespace hal
}    // namespace cooboc

#endif
