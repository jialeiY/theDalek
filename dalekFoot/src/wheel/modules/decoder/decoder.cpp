#include "modules/decoder/decoder.hpp"
#include "modules/math/utility.h"
#include "driver/serial.hpp"



void Decoder::init(void) {
	for (int i=0; i<9; ++i) {
		mBuffer[i] = 0x00;
	}
	reset();
}

void Decoder::reset(void) {
	mOffset = 0;
	mIsSync = false;
	mHasOutput = false;
}


void Decoder::decode(uint8_t byte) {
	if (mIsSync) {
		mBuffer[mOffset] = byte;
		mOffset++;
		if (mOffset == 9) {
			validatePacket();
			invalidatePacket();
		}
	} else {
		if (byte == 0x55)
		{
			mOffset = 1;
			mBuffer[0] = byte;
			mIsSync = true;
		}
	}
}

void Decoder::validatePacket(void) {
	if (mBuffer[8] != 0xAA) return ;
	uint8_t expectCrc = crc8(mBuffer+1, 6);
	if (expectCrc != mBuffer[7]) return ;

	for (int i=0; i<4; ++i) {
		mOutput.power[i] = mBuffer[1+i];
	}
	mOutput.melodyIdx = mBuffer[5];
	mOutput.ledStatus = mBuffer[6];

	mHasOutput = true;

	// Serial1.printf("packet:%2x %2x %2x %2x %2x %2x %2x %2x %2x\r\n", 
	// mBuffer[0], mBuffer[1], mBuffer[2], mBuffer[3], mBuffer[4], mBuffer[5], mBuffer[6], mBuffer[7]);
}


void Decoder::invalidatePacket(void) {
	mOffset = 0;
	mIsSync = false;
}

