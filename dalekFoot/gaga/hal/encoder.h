#ifndef __HAL_ENCODER_ENCODER_H__
#define __HAL_ENCODER_ENCODER_H__

#include <array>
#include <cstdint>

namespace cooboc {
namespace hal {
class Encoder {
  public:
    enum class I2CStatus : uint8_t {
        OK = 0U,
    };
    struct EncoderReading {
        std::uint16_t value;
        I2CStatus i2cStatus;
    };
    using EncoderReadings = std::array<EncoderReading, 4U>;

    Encoder() = default;
    void setup();
    void begin();
    bool triggerReading();
    EncoderReadings getReadings();

  private:
    void i2cfrequencyTest();
    // Move this function to I2C?
    void configTimer5(const std::uint32_t pre, const std::uint32_t period);
    void statisticizeI2cReading(const std::uint32_t pre,
                                const std::uint32_t period);
};

extern Encoder gagaEncoder;
}    // namespace hal
}    // namespace cooboc

#endif
