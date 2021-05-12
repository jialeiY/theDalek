#ifndef __MODULE_SENSING_MCU_DECODER_MCU_USART_DECODER_H__
#define __MODULE_SENSING_MCU_DECODER_MCU_USART_DECODER_H__


#include "module/sensing/mcu_decoder/data_type.h"
#include <stdint.h>
#include <stddef.h>

namespace sensing {


class McuUsartDecoder {
	public:
		McuUsartDecoder();
		virtual ~McuUsartDecoder();
		void reset();
		void decode(const uint8_t *data, size_t length);
		bool hasData() const { return mHasData; };
		McuSensors fetchData() {
			mHasData = false;
			return mOutput;
		}
	private:
		enum DecoderStatus {
			UNSYNC,
			SYNCED
		};
		
		DecoderStatus mStatus;
		size_t mOffset;
		bool mHasData;
		uint8_t mBuffer[51];
		McuSensors mOutput;
		
		inline void decodeByByte(uint8_t byte);
		inline void validateAndOutputPackage();
		void invalidatePacket();
		void outputPacket();
};


}

#endif

