#include "framework/io_thread.h"
#include "framework/event_type.h"
#include "module/math/utility.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>



using namespace std;

IOThread::IOThread(const ThreadHub &hub): IThread(hub) {
	mOutputBuffer[0] = 0x55;	// HEAD
	mOutputBuffer[1] = 0x00;	// MOTOR #1
	mOutputBuffer[2] = 0x00;	// MOTOR #2
	mOutputBuffer[3] = 0x00;	// MOTOR #3
	mOutputBuffer[4] = 0x00;	// MOTOR #4
	mOutputBuffer[5] = 0x00;	// Melody Id
	mOutputBuffer[6] = 0x00;	// LED
	mOutputBuffer[7] = crc8(mOutputBuffer+1, 6);	// CRC
	mOutputBuffer[8] = 0xAA;	// END

	mTtyFd = open("/dev/ttyS3", O_RDWR | O_NOCTTY | O_NDELAY);

	if (mTtyFd <= 0) {
		printf("open file error\r\n");
	} else {
		printf("open file success\r\n");
	}
	termios options;
	tcgetattr(mTtyFd, &options);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;//8N1
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CRTSCTS; //disable hardware control
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //turn off canonical input, choosing raw input
	options.c_iflag &= ~(IXON | IXOFF | IXANY);	//disable software flow control
	options.c_oflag &= ~OPOST;	//raw output
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	tcsetattr(mTtyFd, TCSANOW, &options);
	
	// Set Block read
	fcntl(mTtyFd, F_SETFL, 0);
}

IOThread::~IOThread() {
	close(mTtyFd);

}


void IOThread::work() {
	
}


void IOThread::onNotify(uint64_t eventType) {
	switch (eventType) {
		case (EventType::GLOBAL_CYCLE_START) : {
			// output the data;
			printf("output data\r\n");
			size_t remainLength = 9;
			while (remainLength > 0) {
				ssize_t lengthSent = write(mTtyFd, mOutputBuffer, remainLength);
				if (lengthSent == 0) {
					cout << "send error" << endl;
					break;
				}
				remainLength -= lengthSent;
			}
			break;
		}
		case (EventType::IO_MCU_RESPONSE_TIMEOUT) : {
			printf("response timeout\r\n");
			break;
		}
		default: {
			break;
		}
	}
}


void IOThread::crcPayload() {

}