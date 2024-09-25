#ifndef __HIL__SPI_DRIVER_SPI_DRIVER_H__
#define __HIL__SPI_DRIVER_SPI_DRIVER_H__

#include <ch341/ch341_lib.h>
#include <cstring>
#include <string>
#include "data/gh_protocol.h"

namespace cooboc {
namespace hil {



class Ch341 {
  public:
    Ch341(const char *devicePath) : fd_ {CH34xOpenDevice(devicePath)} {
        if (fd_ < 0) {
            throw(std::string("Device open error: ") + devicePath);
        }

        // Must read chip id first, or the chip won't work.
        unsigned char chipVer;
        CH34x_GetChipVersion(fd_, &chipVer);
        std::printf("Device [%s] opened.\r\n", devicePath);
    }

    ~Ch341() { CH34xCloseDevice(fd_); }

    void setup() {
        std::printf("ch341 fd: %d\r\n", fd_);
        // Set SPI interface in [MSB]
        const std::uint8_t iMode {0x80};
        const bool ret = CH34xSetStream(fd_, iMode);
        if (!ret) {
            std::perror("Init interface failed.\r\n");
        }
    }

    cooboc::comm::GHPacket sendPacket(cooboc::comm::HGPacket tx) {
        cooboc::comm::GHPacket recv;
        if (CH34xStreamSPI4(fd_, 0x80, HG_PACKET_SIZE, &tx)) {
            std::memcpy(&recv, &tx, GH_PACKET_SIZE);
        } else {
            std::perror("RW error\r\n");
        }
        return recv;
    }


  private:
    const int fd_;
};
}    // namespace hil
}    // namespace cooboc
#endif
