#include "module/hardware/usart/wheel_usart.h"
#include "module/hardware/mcu_decoder/mcu_usart_decoder.h"
#include "framework/rtdp/logger/logger.h"
#include "module/mem/mem.h"
#include "module/math/crc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <termios.h>
#include <string>

namespace hardware {
namespace usart {

WheelUsart::WheelUsart() :
	mDecoder() ,
	mHardwareDataPtr(nullptr), 
	mHasResult (false){

	mOutputBuffer[0] = 0x55;					   // HEAD
	mOutputBuffer[1] = 0x00;					   // MOTOR #1
	mOutputBuffer[2] = 0x00;					   // MOTOR #2
	mOutputBuffer[3] = 0x00;					   // MOTOR #3
	mOutputBuffer[4] = 0x00;					   // MOTOR #4
	mOutputBuffer[5] = 0x00;					   // Melody Id
	mOutputBuffer[6] = 0x3F;					   // LED
	mOutputBuffer[7] = math::crc8(mOutputBuffer + 1, 6); // CRC
	mOutputBuffer[8] = 0xAA;					   // END

	// Set non-Block read
	mTtyFd = open("/dev/ttyS3", O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (mTtyFd <= 0) {
		LogFatal("open file failed");
	} else {
		LogInfo("open file success");
	}
	termios options;
	tcgetattr(mTtyFd, &options);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB; //8N1
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CRTSCTS;						//disable hardware control
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //turn off canonical input, choosing raw input
	options.c_iflag &= ~(IXON | IXOFF | IXANY);			//disable software flow control
	options.c_oflag &= ~OPOST;							//raw output
	cfsetispeed(&options, B115200);
	// cfsetospeed(&options, B9600);
	tcsetattr(mTtyFd, TCSANOW, &options);

	mDecoder.reset();
}

WheelUsart::~WheelUsart() {
	close(mTtyFd);
}

void WheelUsart::startCycle(volatile struct data_types::HardwareData *data) {
	mHardwareDataPtr = data;
	mHasResult = false;
	clearUsartInputBuffer();
	writeUsart();
	// reset decoder
	mDecoder.reset();
}

void WheelUsart::endCycle() {
	if (!mHasResult) {
		// mDecoder.printDebugInfo();
	}
}


void WheelUsart::clearUsartInputBuffer(void) const {
	std::uint8_t buffer[24];
	int lenRead = 0;
	do {
		lenRead = read(mTtyFd, buffer, 24);
	} while (lenRead > 0);
}

void WheelUsart::writeUsart(void) {
	// for debug
	// LogInfo("ready to write speed: %d", mHardwareDataPtr->output.value);
	mOutputBuffer[4] = mHardwareDataPtr->output.value;
	mOutputBuffer[7] = math::crc8(mOutputBuffer + 1, 6); // CRC

	size_t remainLength = 9;
	while (remainLength > 0) {
		ssize_t lengthSent = write(mTtyFd, mOutputBuffer, remainLength);
		if (lengthSent <= 0) {
			LogError("send error");
			break;
		}
		remainLength -= lengthSent;
	}
}

void WheelUsart::tick(void) {
	int lenRead = read(mTtyFd, mInputBuffer, 64);
	if (lenRead > 0) {
		LogInfo("decode %d", lenRead);
		mDecoder.decode(mInputBuffer, lenRead);
		if (mDecoder.hasData()) {
			const std::uint8_t *packet = mDecoder.fetchData();

			// Filling the packet to output area
			mHardwareDataPtr->input.mcuSensors.timestampMsec = math::u8array2u32(packet+1);
			mHardwareDataPtr->input.mcuSensors.timestampUsec = math::u8array2u32(packet+5);
			for (int i=0; i<4; ++i) {
				mHardwareDataPtr->input.mcuSensors.motorEncoder[i] = math::u8array2u16(packet+9 + i*2);
			}
			for (int i=0; i<14; ++i) {
				mHardwareDataPtr->input.mcuSensors.fastAdc[i] = math::u8array2u16(packet+17 + i*2);
			}
			mHardwareDataPtr->input.mcuSensors.slowAdcIdx = packet[45];
			mHardwareDataPtr->input.mcuSensors.slowAdcIdx = math::u8array2u16(packet+46);
			mHardwareDataPtr->input.mcuSensors.userInput = packet[48];
			
			// Set the qualifier
			mHardwareDataPtr->input.mcuSensors.qualifier = data_types::Qualifier::QUALIFIER_READ_OK;

			mHasResult = true;
		}
	} else if (lenRead < 0) {
		// printf("Error reading file: %s\n", strerror( errno ));	
	}
}

}
}

