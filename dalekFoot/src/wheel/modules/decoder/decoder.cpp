#include "modules/decoder/decoder.hpp"
#include "modules/math/utility.h"




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
		
	} else {
		if (byte == 0x55)
		{
			mOffset = 1;
			mBuffer[0] = byte;
			mIsSync = true;
		} else {
			mBuffer[mOffset] = byte;
			mOffset++;
			if (mOffset == 9) {
				validatePacket();
				invalidatePacket();
			}
		}
	}
}

void Decoder::validatePacket(void) {
	if (mBuffer[8] != 0xAA) return ;
	uint8_t expectCrc = crc8(mBuffer+1, 6);
	if (expectCrc != mBuffer[7]) return ;

	for (int i=0; i<4; ++i) {
		mOutput.power[i] = u8array2u16(mBuffer + (1 + i*2));
	}
	mOutput.melodyIdx = mBuffer[5];
	mOutput.ledStatus = mBuffer[6];

	mHasOutput = true;
}


void Decoder::invalidatePacket(void) {
	mOffset = 0;
	mIsSync = false;
}

