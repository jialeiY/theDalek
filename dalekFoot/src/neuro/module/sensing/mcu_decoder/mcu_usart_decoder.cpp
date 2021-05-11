#include "module/sensing/mcu_decoder/mcu_usart_decoder.h"
#include "module/math/utility.h"


namespace sensing {




McuUsartDecoder::McuUsartDecoder() 
	:mStatus(DecoderStatus::UNSYNC),
	mOffset(0U),
	mHasData(false) {

}


McuUsartDecoder::~McuUsartDecoder() {

}


void McuUsartDecoder::reset() {
	mStatus = DecoderStatus::UNSYNC;
	mOffset = 0U;
	mHasData = false;
}


void McuUsartDecoder::decode(const uint8_t *data, size_t length) {
	for (size_t i=0; i<length; ++i) {
		decodeByByte(data[i]);
	}
}

inline void McuUsartDecoder::decodeByByte(uint8_t byte) {
	switch (mStatus) {
		case (DecoderStatus::UNSYNC) : {
			if (byte == 0x55) {
				mBuffer[0] = byte;
				mOffset = 1;
				mStatus = DecoderStatus::SYNCED;
			}
			break;
		}
		case (DecoderStatus::SYNCED) : {
			mBuffer[mOffset] = byte;
			mOffset ++;
			if (mOffset == 50) {
				validateAndOutputPackage();
			}
			break;
		}
		default: {
			// TODO: ERROR(unknown status);
			reset();
			break;
		}
	}
}


inline void McuUsartDecoder::validateAndOutputPackage() {
	if (mBuffer[8] != 0xAA) {
		invalidatePacket();
		return ;
	}

	uint8_t expectCrc = crc8(mBuffer+1, 47);
	if (expectCrc != mBuffer[48]) {
		invalidatePacket();
		return ;
	}
	outputPacket();
}



void McuUsartDecoder::invalidatePacket() {
	mStatus = DecoderStatus::UNSYNC;
	mOffset = 0U;
}

void McuUsartDecoder::outputPacket() {
		mOutput.timestampMsec = u8array2u32(mBuffer+1);
		mOutput.timestampUsec = u8array2u32(mBuffer+5);
		for (int i=0; i<4; ++i) {
			mOutput.motorEncoder[i] = u8array2u16(mBuffer+9 + i*2);
		}
		for (int i=0; i<14; ++i) {
			mOutput.fastAdc[i] = u8array2u16(mBuffer+17 + i*2);
		}
		mOutput.slowAdcIdx = mBuffer[45];
		mOutput.slowAdcIdx = u8array2u16(mBuffer+46);
		mOutput.userInput = mBuffer[47];

		mHasData = true;

}


}