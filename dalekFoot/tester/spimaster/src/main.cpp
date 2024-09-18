#include <ch341_lib.h>
#include <data/gh_protocol.h>
#include <linux/byteorder/little_endian.h>
#include <unistd.h>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern "C" {

constexpr char devicePath[] {"/dev/ch34x_pis0"};

namespace cooboc {

std::uint64_t milliseconds() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}


class Ch341 {
  public:
    Ch341(const char *devicePath) : fd_ {CH34xOpenDevice(devicePath)}, cnt_ {0x11223344} {
        if (fd_ < 0) {
            std::perror("Device open error");
            throw -1;
        }

        // Must read chip id first, or the chip won't work.
        unsigned char chipver;
        CH34x_GetChipVersion(fd_, &chipver);
        std::printf("Device [%s] opened.\r\n", devicePath);
    }

    ~Ch341() { CH34xCloseDevice(fd_); }

    void setup() {
        std::printf("fd: %d\r\n", fd_);
        // Set SPI interface in [MSB]
        const std::uint8_t iMode {0x80};
        const bool ret = CH34xSetStream(fd_, iMode);
        if (!ret) {
            std::perror("Init interface failed.\r\n");
        }
    }

    void sendPacket(cooboc::comm::HGPacket spi) {
        if (CH34xStreamSPI4(fd_, 0x80, HG_PACKET_SIZE, &spi)) {
            // std::printf("value: %d %x%x%x%x.\r\n", cnt_, buffer[0], buffer[1], buffer[2],
            // buffer[3]);
        } else {
            std::perror("RW error\r\n");
        }
    }

    void test() {
        cooboc::comm::HGPacket spi;

        // spi.wheelsPlanning[40][3] = 0;
        //  spi.motorPower[0]         = 10;
        int s;


        std::cin >> s;
        auto begin = std::chrono::steady_clock::now();
        for (std::size_t i {0U}; i < 4U; ++i) {
            for (std::size_t j {0U}; j < 10U; ++j) {
                //
                spi.wheelsPlanning[i][j] = s;
            }
        }
        // spi.motorPower[0] = s;

        // std::uint8_t buffer[sizeof(int)];
        // *(int *)(buffer) = __cpu_to_le32(cnt_);
        // // buffer[0] = 0xAA;
        // // buffer[1] = 0xBB;
        // // buffer[2] = 0xCC;
        // // buffer[3] = 0xDD;
        if (CH34xStreamSPI4(fd_, 0x80, HG_PACKET_SIZE, &spi)) {
            // std::printf("value: %d %x%x%x%x.\r\n", cnt_, buffer[0], buffer[1], buffer[2],
            // buffer[3]);
        } else {
            std::perror("RW error\r\n");
        }
        auto end = std::chrono::steady_clock::now();
        std::uint64_t duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();


        std::cout << "duration: " << duration << std::endl;
        cnt_++;
    }

  private:
    const int fd_;
    unsigned int cnt_;
};

}    // namespace cooboc

int main() {
    cooboc::Ch341 ch341(devicePath);

    ch341.setup();

    // while (true) {
    //     ch341.test();
    //     usleep(50ULL * 1000LL);
    // }

    cooboc::comm::HGPacket spi;
    std::uint64_t count {0U};

    while (true) {
        auto begin = std::chrono::steady_clock::now();
        count += 10;    // 10ms once
        count %= 3000;
        for (std::size_t offset {0U}; offset < 10U; offset++) {
            float point =
              static_cast<float>((count + 10U * offset) % 3000) / 3000.0F * 2 * 3.1415926;
            float value = (std::sin(point) + 1.0F) * 10.0F + 10.0F;
            for (std::size_t i {0U}; i < 4U; ++i) { spi.wheelsPlanning[i][offset] = value; }
        }

        while (true) {
            auto now = std::chrono::steady_clock::now();
            std::uint64_t duration =
              std::chrono::duration_cast<std::chrono::microseconds>(now - begin).count();
            if (duration > 10000) {
                break;
            }
        }
        // std::cout << "o" << std::flush;
        ch341.sendPacket(spi);
    }

    return 0;
}
}