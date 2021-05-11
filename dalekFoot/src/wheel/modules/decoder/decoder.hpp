#ifndef __MODULES_DECODER_DECODER_H__
#define __MODULES_DECODER_DECODER_H__

#include <stdint.h>
#include "inc.h"
#include <string.h>

struct ContorlRequestPacket {
	int8_t power[4];
	uint8_t melodyIdx;
	uint8_t ledStatus;

ContorlRequestPacket() {
		power[0] = 0;
		power[1] = 0;
		power[2] = 0;
		power[3] = 0;
		melodyIdx = 0;
		ledStatus = 0;
	}

	ContorlRequestPacket(volatile const ContorlRequestPacket& obj) {
		power[0] = obj.power[0];
		power[1] = obj.power[1];
		power[2] = obj.power[2];
		power[3] = obj.power[3];
		melodyIdx = obj.melodyIdx;
		ledStatus = obj.ledStatus;
	}

	ContorlRequestPacket(const ContorlRequestPacket& obj) {
		power[0] = obj.power[0];
		power[1] = obj.power[1];
		power[2] = obj.power[2];
		power[3] = obj.power[3];
		melodyIdx = obj.melodyIdx;
		ledStatus = obj.ledStatus;
	}

	ContorlRequestPacket operator = (const ContorlRequestPacket& obj) {
		power[0] = obj.power[0];
		power[1] = obj.power[1];
		power[2] = obj.power[2];
		power[3] = obj.power[3];
		melodyIdx = obj.melodyIdx;
		ledStatus = obj.ledStatus;
		return *this;
	}

	ContorlRequestPacket operator = (volatile const ContorlRequestPacket& obj) {
		power[0] = obj.power[0];
		power[1] = obj.power[1];
		power[2] = obj.power[2];
		power[3] = obj.power[3];
		melodyIdx = obj.melodyIdx;
		ledStatus = obj.ledStatus;
		return *this;
	}


};

class Decoder {
	public:
		void init(void);
		void reset(void);
		void decode(uint8_t byte);
		inline bool hasOutput(void) const {
			return mHasOutput;
		}
		inline ContorlRequestPacket fetchOutput(void) {
			mHasOutput = false;
			return mOutput;
		}
		
	private:
		bool mIsSync;
		bool mHasOutput;
		uint8_t mBuffer[9];
		uint8_t mOffset;
		volatile ContorlRequestPacket mOutput;

		void validatePacket(void);
		void invalidatePacket(void);
};


#endif


