#include <cstdint>
#include <ch341_lib.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <linux/byteorder/little_endian.h>

extern "C"
{

    constexpr char devicePath[]{"/dev/ch34x_pis3"};

    namespace cooboc
    {
        class Ch341
        {
        public:
            Ch341(const char *devicePath) : fd_{CH34xOpenDevice(devicePath)}, cnt_{0x11223344}
            {

                if (fd_ < 0)
                {
                    std::perror("Device open error");
                    throw -1;
                }

                // Must read chip id first, or the chip won't work.
                unsigned char chipver;
                CH34x_GetChipVersion(fd_, &chipver);
                std::printf("Device [%s] opened.\r\n", devicePath);
            }

            ~Ch341()
            {
                CH34xCloseDevice(fd_);
            }

            void setup()
            {
                std::printf("fd: %d\r\n", fd_);
                // Set SPI interface in [MSB]
                const std::uint8_t iMode{0x80};
                const bool ret = CH34xSetStream(fd_, iMode);
                if (!ret)
                {
                    std::perror("Init interface failed.\r\n");
                }
            }

            void test()
            {
                std::uint8_t buffer[sizeof(int)];
                *(int *)(buffer) = __cpu_to_le32(cnt_);
                // buffer[0] = 0xAA;
                // buffer[1] = 0xBB;
                // buffer[2] = 0xCC;
                // buffer[3] = 0xDD;
                if (CH34xStreamSPI4(fd_, 0x80, sizeof(int), buffer))
                {
                    std::printf("value: %d %x%x%x%x.\r\n", cnt_, buffer[0], buffer[1], buffer[2], buffer[3]);
                }
                else
                {
                    std::perror("RW error\r\n");
                }
                cnt_++;
            }

        private:
            const int fd_;
            unsigned int cnt_;
        };

    }

    int main()
    {
        cooboc::Ch341 ch341(devicePath);

        ch341.setup();

        while (true)
        {
            ch341.test();
            usleep(500ULL * 1000LL);
        }

        return 0;
    }
}