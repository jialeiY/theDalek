#include "spi.h"
#include <utils/logger.h>
#include <cstring>
#include <cstring>

Spi::Spi() {
	Ldebug("ready to initalize SPI");
	// initialize transfer control register
	memset(&mTransferControl, 0, sizeof(spi_ioc_transfer));
	mTransferControl.speed_hz = 100000;  // default speed 100kHz
	mTransferControl.bits_per_word = 8;
	mSpiFd = open("/dev/spidev0.0", O_RDWR);
	if (mSpiFd < 0) throw string("Failed to open SPI device @ ") + "/dev/spidev0.0";
	int ret = 0;

	uint8_t mode = 0;
	ret = ioctl(mSpiFd, SPI_IOC_WR_MODE, &mode);
	if (ret < 0) throw string("Failed to set mode");
	ret = ioctl(mSpiFd, SPI_IOC_RD_MODE, &mode);
	if (ret < 0) throw string("Failed to get mode");

	uint8_t bits = 8;
	ret = ioctl(mSpiFd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret < 0) throw string("Failed to set bits per words");
	ret = ioctl(mSpiFd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret < 0) throw string("Failed to get bits per words");
	
	ret = ioctl(mSpiFd, SPI_IOC_WR_MAX_SPEED_HZ, &(mTransferControl.speed_hz));
	if (ret < 0) throw string("Failed to set spped hz");
	ret = ioctl(mSpiFd, SPI_IOC_RD_MAX_SPEED_HZ, &(mTransferControl.speed_hz));
	if (ret < 0) throw string("Failed to get spped hz");
}

Spi::~Spi() {
	Ldebug("deinitializing SPI");
}

void Spi::setBaudrate(uint32_t baudrate) {
	mTransferControl.speed_hz = baudrate;
}


void Spi::transfer(const uint8_t* txBuf, uint8_t* rxBuf, size_t len) {
	mTransferControl.tx_buf = (uint64_t)txBuf;
	mTransferControl.rx_buf = (uint64_t)rxBuf;
	mTransferControl.len = len;
	int ret = ioctl(mSpiFd, SPI_IOC_MESSAGE(1), &mTransferControl);

	if (ret < 1) {
		Lerror("SPI failed, errno: %d, err: %s", errno, strerror(errno));
	} 
}
