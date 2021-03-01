#ifndef __MCP2515_H__
#define __MCP2515_H__

#include <driver/can.h>
#include <driver/spi.h>
#include <stdint.h>


class Mcp2515 : public Can {
	public:
		explicit Mcp2515();
		virtual ~Mcp2515();
	private:
		void gotoConfigurationMode();
		void write(const uint8_t addr, const uint8_t data);
		uint8_t readRegister(const uint8_t addr);

		Spi mSpi;
};

#endif
