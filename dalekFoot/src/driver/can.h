#ifndef __CAN_H__
#define __CAN_H__


#include <driver/spi.h>


class Can {
	public:
		Can();
		virtual ~Can();
		enum CanSpeed {
			CAN_5KBPS = 0,
			CAN_10KBPS,
			CAN_20KBPS,
			CAN_31K25BPS,
			CAN_33KBPS,
			CAN_40KBPS,
			CAN_50KBPS,
			CAN_80KBPS,
			CAN_83K3BPS,
			CAN_95KBPS,
			CAN_100KBPS,
			CAN_125KBPS,
			CAN_200KBPS,
			CAN_250KBPS,
			CAN_500KBPS,
			CAN_1000KBPS
		};

		virtual void sendStandardMessage(uint32_t id, const uint8_t *data, uint8_t len) = 0;
};

#endif
