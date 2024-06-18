#ifndef __HAL_SERIAL_H__
#define __HAL_SERIAL_H__
namespace cooboc {
namespace hal {
class GagaSerial {
  public:
    GagaSerial();
    void setup();
    void tick();
    int println(const char* format, ...);
};

extern GagaSerial gagaSerial;

}    // namespace hal
}    // namespace cooboc


#endif
