#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include <cstdint>
#include <functional>

namespace cooboc {
namespace hal {

struct SpiProtocol {
    std::int8_t motorPower[4];
};

class GagaSpi {
    using OnDataReceivedCallback = std::function<void(const SpiProtocol &)>;

  public:
    GagaSpi();
    void setup(const OnDataReceivedCallback callback);
    void tick();
    void begin();

    inline void __onDataReceived();

  private:
    OnDataReceivedCallback dataReceivedCallback_;
};

extern GagaSpi gagaSpi;

}    // namespace hal
}    // namespace cooboc

#endif
