#include "module/hardware/mcu_decoder/mcu_usart_decoder.h"
#include "module/math/crc.h"
#include "module/math/bitop.h"
#include "framework/rtdp/logger/logger.h"
#include <cstdio>
#include <cstring>
#include <string>


namespace hardware {

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
	// if (data[0] == 0x55) LogDebug("should sync, current status: %d", mStatus);
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
			if (mOffset == 51) {
				validateAndOutputPackage();
				invalidatePacket();
			}
			break;
		}
		default: {
			LogError("Unknown status of McuUsart");
			reset();
			break;
		}
	}
}


inline void McuUsartDecoder::validateAndOutputPackage() {
	if (mBuffer[50] != 0xAA) {
		return ;
	}

	uint8_t expectCrc = math::crc8(mBuffer+1, 48);
	if (expectCrc != mBuffer[49]) {
		return ;
	}
	mHasData = true;
}



void McuUsartDecoder::invalidatePacket() {
	mStatus = DecoderStatus::UNSYNC;
	mOffset = 0U;
}



void McuUsartDecoder::printDebugInfo() {
	LogDebug("status: %s, offset: %ld", 
		(mStatus == DecoderStatus::UNSYNC ? "unsync" : "synced"), 
		mOffset);
		if (mStatus == DecoderStatus::SYNCED) {
			std::string output;
			char buffer[28];
			for (int i=0; i<mOffset; ++i) {
				sprintf(buffer, "%02X ", mBuffer[i]);
				output += buffer;
			}
			LogDebug("buffer: %s", output.c_str());
		}
}

}