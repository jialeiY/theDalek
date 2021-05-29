#ifndef __MODULE_HARDWARE_MCU_DECODER_MCU_USART_DECODER_H__
#define __MODULE_HARDWARE_MCU_DECODER_MCU_USART_DECODER_H__


#include "module/data_types/hardware/mcu_sensors.h"
#include <cstdint>
#include <stddef.h>

namespace hardware {


class McuUsartDecoder {
	public:
		McuUsartDecoder();
		virtual ~McuUsartDecoder();
		void reset();
		void printDebugInfo();
		void decode(const uint8_t *data, size_t length);
		bool hasData() const { return mHasData; };
		const std::uint8_t * fetchData() {
			mHasData = false;
			return mBuffer;
		}
	private:
		enum DecoderStatus : std::uint8_t {
			UNSYNC = 0,
			SYNCED = 1
		};
		
		DecoderStatus mStatus;
		size_t mOffset;
		bool mHasData;
		uint8_t mBuffer[51];
		
		inline void decodeByByte(uint8_t byte);
		inline void validateAndOutputPackage();
		void invalidatePacket();
};


}

#endif

