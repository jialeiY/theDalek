#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

class Spi {
	public:
		Spi();
		virtual ~Spi();

		void setBaudrate(uint32_t baudrate);
		void transfer(const uint8_t* txBuf, uint8_t* rxBuf, size_t len);
	private:
		spi_ioc_transfer mTransferControl;
		int mSpiFd;
};


#endif