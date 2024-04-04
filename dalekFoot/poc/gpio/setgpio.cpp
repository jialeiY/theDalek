#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

int main() {
    int fd;
    struct gpiohandle_request led, button;
    struct gpiohandle_data data;

    // open gpiochip device file
    fd = open("/dev/gpiochip0", O_RDWR);
    if (fd < 0) {
        std::perror("Error openning gpiochip0\r\n");
        return -1;
    }

    // Setup LED to output
    led.flags = GPIOHANDLE_REQUEST_OUTPUT;
    strcpy(led.consumer_label, "LED");
    memset(led.default_values, 0, sizeof(led.default_values));
    led.lines = 1;
    led.lineoffsets[0] = 16;

    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &led) < 0) {
        std::perror("Error setting GPIO 16 to output");
        close (fd);
        return -1;
    }

    // SET THE LED
    bool status {false};
    while (true) {
        data.values[0] = status ? 1:0;
        status = !status;
        if (ioctl(led.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0) {
            std::perror("Error setting GPIO");
        }
    }

    sleep(5);
    close(fd);



    return 0;
}