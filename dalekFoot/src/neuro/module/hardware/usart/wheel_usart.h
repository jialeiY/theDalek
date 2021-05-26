#ifndef __MODULE_HARDWARE_USART_WHEEL_USART_H__
#define __MODULE_HARDWARE_USART_WHEEL_USART_H__

#include "module/data_types/exchange_area.h"
#include "module/hardware/mcu_decoder/mcu_usart_decoder.h"
#include <cstdint>

namespace hardware {
namespace usart {

class WheelUsart {
	public:
		WheelUsart();
		virtual ~WheelUsart();
		virtual void startCycle(volatile struct data_types::ExchangeArea *data);
		virtual void endCycle();
		virtual void tick(void);
		inline bool hasResult(void) const {return mHasResult;}
	private:
		int mTtyFd;
		std::uint8_t mOutputBuffer[9];
		std::uint8_t mInputBuffer[32];
		hardware::McuUsartDecoder mDecoder;

		void clearUsartInputBuffer(void) const;
		void writeUsart(void);

		volatile struct data_types::ExchangeArea *mExchangeArea;
		bool mHasResult;
};

}
}
#endif


