#include "mcp2515.h"
#include <utils/logger.h>

Mcp2515::Mcp2515() {
	Ldebug("MCP2515 inializaing...");

	mSpi.setBaudrate(5000000);
	gotoConfigurationMode();

	// read configruation
	uint8_t data = this->readRegister(0x0F);
	Ldebug("Register CANCTRL: %x", data);
	// data should be equal to 87...
	if (data != 0x87) throw string("configuration from MCP2515 invalid");
}
Mcp2515::~Mcp2515() {}


void Mcp2515::gotoConfigurationMode() {
	// write 0x87 to 0x0F
	this->write(0x0F, 0x87);
}

void Mcp2515::write(const uint8_t addr, const uint8_t data) {
	uint8_t txBuf[3] {0x02, addr, data};
	uint8_t rxBuf[3] {0};
	mSpi.transfer(txBuf, rxBuf, 3);
}


uint8_t Mcp2515::readRegister(const uint8_t addr) {
	uint8_t txBuf[3] {0x03, addr, 0x00};
	uint8_t rxBuf[3] {0};
	mSpi.transfer(txBuf, rxBuf, 3);
	return rxBuf[2];
}