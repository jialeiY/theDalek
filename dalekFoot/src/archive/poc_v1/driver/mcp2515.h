#ifndef __MCP2515_H__
#define __MCP2515_H__

#include <driver/can.h>
#include <driver/spi.h>
#include <stdint.h>


class Mcp2515 : public Can {
	public:
		enum Status {
			CONFIGURATION,
			NORMAL
		};

		explicit Mcp2515();
		virtual ~Mcp2515();
		void setCanSpeed(CanSpeed speed);
		void setNormalMode();
		
		virtual void sendStandardMessage(uint32_t id, const uint8_t *data, uint8_t len);
	private:
		enum McpClock {
			MCP_8MHZ = 0,
			MCP_20MHZ = 1,
			MCP_16MHZ = 2
		};

		void reset();
		void init();
		void setConfigurationMode();
		
		void setSpeed(McpClock mcpClock, CanSpeed speed);
		void writeRegister(const uint8_t addr, const uint8_t data);
		uint8_t readRegister(const uint8_t addr);
		void readRegisters(const int8_t addr, uint8_t rxBuf[], size_t len);
		void writeRegisters(const uint8_t addr, const uint8_t data[], size_t len);
		void modifyBit(const uint8_t addr, const uint8_t mask, const uint8_t data);
		uint8_t readStatus();		
		Spi mSpi;
		Status mStatus;
};

#endif
