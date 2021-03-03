#include "mcp2515.h"
#include <utils/logger.h>


/*
 *  Speed 8M
 */
#define MCP_8MHz_1000kBPS_CFG1 (0x00)
#define MCP_8MHz_1000kBPS_CFG2 (0x80)
#define MCP_8MHz_1000kBPS_CFG3 (0x80)

#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x82)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xB1)
#define MCP_8MHz_250kBPS_CFG3 (0x85)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xB4)
#define MCP_8MHz_200kBPS_CFG3 (0x86)

#define MCP_8MHz_125kBPS_CFG1 (0x01)
#define MCP_8MHz_125kBPS_CFG2 (0xB1)
#define MCP_8MHz_125kBPS_CFG3 (0x85)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xB4)
#define MCP_8MHz_100kBPS_CFG3 (0x86)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xBF)
#define MCP_8MHz_80kBPS_CFG3 (0x87)

#define MCP_8MHz_50kBPS_CFG1 (0x03)
#define MCP_8MHz_50kBPS_CFG2 (0xB4)
#define MCP_8MHz_50kBPS_CFG3 (0x86)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xBF)
#define MCP_8MHz_40kBPS_CFG3 (0x87)

#define MCP_8MHz_33k3BPS_CFG1 (0x47)
#define MCP_8MHz_33k3BPS_CFG2 (0xE2)
#define MCP_8MHz_33k3BPS_CFG3 (0x85)

#define MCP_8MHz_31k25BPS_CFG1 (0x07)
#define MCP_8MHz_31k25BPS_CFG2 (0xA4)
#define MCP_8MHz_31k25BPS_CFG3 (0x84)

#define MCP_8MHz_20kBPS_CFG1 (0x07)
#define MCP_8MHz_20kBPS_CFG2 (0xBF)
#define MCP_8MHz_20kBPS_CFG3 (0x87)

#define MCP_8MHz_10kBPS_CFG1 (0x0F)
#define MCP_8MHz_10kBPS_CFG2 (0xBF)
#define MCP_8MHz_10kBPS_CFG3 (0x87)

#define MCP_8MHz_5kBPS_CFG1 (0x1F)
#define MCP_8MHz_5kBPS_CFG2 (0xBF)
#define MCP_8MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 16M
 */
#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_125kBPS_CFG1 (0x03)
#define MCP_16MHz_125kBPS_CFG2 (0xF0)
#define MCP_16MHz_125kBPS_CFG3 (0x86)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_83k3BPS_CFG1 (0x03)
#define MCP_16MHz_83k3BPS_CFG2 (0xBE)
#define MCP_16MHz_83k3BPS_CFG3 (0x07)

#define MCP_16MHz_50kBPS_CFG1 (0x07)
#define MCP_16MHz_50kBPS_CFG2 (0xFA)
#define MCP_16MHz_50kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

#define MCP_16MHz_33k3BPS_CFG1 (0x4E)
#define MCP_16MHz_33k3BPS_CFG2 (0xF1)
#define MCP_16MHz_33k3BPS_CFG3 (0x85)

#define MCP_16MHz_20kBPS_CFG1 (0x0F)
#define MCP_16MHz_20kBPS_CFG2 (0xFF)
#define MCP_16MHz_20kBPS_CFG3 (0x87)

#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

#define MCP_16MHz_5kBPS_CFG1 (0x3F)
#define MCP_16MHz_5kBPS_CFG2 (0xFF)
#define MCP_16MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 20M
 */
#define MCP_20MHz_1000kBPS_CFG1 (0x00)
#define MCP_20MHz_1000kBPS_CFG2 (0xD9)
#define MCP_20MHz_1000kBPS_CFG3 (0x82)

#define MCP_20MHz_500kBPS_CFG1 (0x00)
#define MCP_20MHz_500kBPS_CFG2 (0xFA)
#define MCP_20MHz_500kBPS_CFG3 (0x87)

#define MCP_20MHz_250kBPS_CFG1 (0x41)
#define MCP_20MHz_250kBPS_CFG2 (0xFB)
#define MCP_20MHz_250kBPS_CFG3 (0x86)

#define MCP_20MHz_200kBPS_CFG1 (0x01)
#define MCP_20MHz_200kBPS_CFG2 (0xFF)
#define MCP_20MHz_200kBPS_CFG3 (0x87)

#define MCP_20MHz_125kBPS_CFG1 (0x03)
#define MCP_20MHz_125kBPS_CFG2 (0xFA)
#define MCP_20MHz_125kBPS_CFG3 (0x87)

#define MCP_20MHz_100kBPS_CFG1 (0x04)
#define MCP_20MHz_100kBPS_CFG2 (0xFA)
#define MCP_20MHz_100kBPS_CFG3 (0x87)

#define MCP_20MHz_83k3BPS_CFG1 (0x04)
#define MCP_20MHz_83k3BPS_CFG2 (0xFE)
#define MCP_20MHz_83k3BPS_CFG3 (0x87)

#define MCP_20MHz_80kBPS_CFG1 (0x04)
#define MCP_20MHz_80kBPS_CFG2 (0xFF)
#define MCP_20MHz_80kBPS_CFG3 (0x87)

#define MCP_20MHz_50kBPS_CFG1 (0x09)
#define MCP_20MHz_50kBPS_CFG2 (0xFA)
#define MCP_20MHz_50kBPS_CFG3 (0x87)

#define MCP_20MHz_40kBPS_CFG1 (0x09)
#define MCP_20MHz_40kBPS_CFG2 (0xFF)
#define MCP_20MHz_40kBPS_CFG3 (0x87)

#define MCP_20MHz_33k3BPS_CFG1 (0x0B)
#define MCP_20MHz_33k3BPS_CFG2 (0xFF)
#define MCP_20MHz_33k3BPS_CFG3 (0x87)



static const uint8_t MCP_SPEED_CONFIG[3][3][16] {
	{
		{MCP_8MHz_5kBPS_CFG1, MCP_8MHz_10kBPS_CFG1, MCP_8MHz_20kBPS_CFG1, MCP_8MHz_31k25BPS_CFG1, MCP_8MHz_33k3BPS_CFG1, MCP_8MHz_40kBPS_CFG1, MCP_8MHz_50kBPS_CFG1, MCP_8MHz_80kBPS_CFG1, 0, 0, MCP_8MHz_100kBPS_CFG1, MCP_8MHz_125kBPS_CFG1, MCP_8MHz_200kBPS_CFG1, MCP_8MHz_250kBPS_CFG1, MCP_8MHz_500kBPS_CFG1, MCP_8MHz_1000kBPS_CFG1},
		{MCP_16MHz_5kBPS_CFG1, MCP_16MHz_10kBPS_CFG1, MCP_16MHz_20kBPS_CFG1, 0, MCP_16MHz_33k3BPS_CFG1, MCP_16MHz_40kBPS_CFG1, MCP_16MHz_50kBPS_CFG1, MCP_16MHz_80kBPS_CFG1, MCP_16MHz_83k3BPS_CFG1, 0, MCP_16MHz_100kBPS_CFG1, MCP_16MHz_125kBPS_CFG1, MCP_16MHz_200kBPS_CFG1, MCP_16MHz_250kBPS_CFG1, MCP_16MHz_500kBPS_CFG1, MCP_16MHz_1000kBPS_CFG1},
		{0, 0, 0, 0, MCP_20MHz_33k3BPS_CFG1, MCP_20MHz_40kBPS_CFG1, MCP_20MHz_50kBPS_CFG1, MCP_20MHz_80kBPS_CFG1, MCP_20MHz_83k3BPS_CFG1, 0, MCP_20MHz_100kBPS_CFG1, MCP_20MHz_125kBPS_CFG1, MCP_20MHz_200kBPS_CFG1, MCP_20MHz_250kBPS_CFG1, MCP_20MHz_500kBPS_CFG1, MCP_20MHz_1000kBPS_CFG1}
	},
	{
		{MCP_8MHz_5kBPS_CFG2, MCP_8MHz_10kBPS_CFG2, MCP_8MHz_20kBPS_CFG2, MCP_8MHz_31k25BPS_CFG2, MCP_8MHz_33k3BPS_CFG2, MCP_8MHz_40kBPS_CFG2, MCP_8MHz_50kBPS_CFG2, MCP_8MHz_80kBPS_CFG2, 0, 0, MCP_8MHz_100kBPS_CFG2, MCP_8MHz_125kBPS_CFG2, MCP_8MHz_200kBPS_CFG2, MCP_8MHz_250kBPS_CFG2, MCP_8MHz_500kBPS_CFG2, MCP_8MHz_1000kBPS_CFG2},
		{MCP_16MHz_5kBPS_CFG2, MCP_16MHz_10kBPS_CFG2, MCP_16MHz_20kBPS_CFG2, 0, MCP_16MHz_33k3BPS_CFG2, MCP_16MHz_40kBPS_CFG2, MCP_16MHz_50kBPS_CFG2, MCP_16MHz_80kBPS_CFG2, MCP_16MHz_83k3BPS_CFG2, 0, MCP_16MHz_100kBPS_CFG2, MCP_16MHz_125kBPS_CFG2, MCP_16MHz_200kBPS_CFG2, MCP_16MHz_250kBPS_CFG2, MCP_16MHz_500kBPS_CFG2, MCP_16MHz_1000kBPS_CFG2},
		{0, 0, 0, 0, MCP_20MHz_33k3BPS_CFG2, MCP_20MHz_40kBPS_CFG2, MCP_20MHz_50kBPS_CFG2, MCP_20MHz_80kBPS_CFG2, MCP_20MHz_83k3BPS_CFG2, 0, MCP_20MHz_100kBPS_CFG2, MCP_20MHz_125kBPS_CFG2, MCP_20MHz_200kBPS_CFG2, MCP_20MHz_250kBPS_CFG2, MCP_20MHz_500kBPS_CFG2, MCP_20MHz_1000kBPS_CFG2}
	},
	{
		{MCP_8MHz_5kBPS_CFG3, MCP_8MHz_10kBPS_CFG3, MCP_8MHz_20kBPS_CFG3, MCP_8MHz_31k25BPS_CFG3, MCP_8MHz_33k3BPS_CFG3, MCP_8MHz_40kBPS_CFG3, MCP_8MHz_50kBPS_CFG3, MCP_8MHz_80kBPS_CFG3, 0, 0, MCP_8MHz_100kBPS_CFG3, MCP_8MHz_125kBPS_CFG3, MCP_8MHz_200kBPS_CFG3, MCP_8MHz_250kBPS_CFG3, MCP_8MHz_500kBPS_CFG3, MCP_8MHz_1000kBPS_CFG3},
		{MCP_16MHz_5kBPS_CFG3, MCP_16MHz_10kBPS_CFG3, MCP_16MHz_20kBPS_CFG3, 0, MCP_16MHz_33k3BPS_CFG3, MCP_16MHz_40kBPS_CFG3, MCP_16MHz_50kBPS_CFG3, MCP_16MHz_80kBPS_CFG3, MCP_16MHz_83k3BPS_CFG3, 0, MCP_16MHz_100kBPS_CFG3, MCP_16MHz_125kBPS_CFG3, MCP_16MHz_200kBPS_CFG3, MCP_16MHz_250kBPS_CFG3, MCP_16MHz_500kBPS_CFG3, MCP_16MHz_1000kBPS_CFG3},
		{0, 0, 0, 0, MCP_20MHz_33k3BPS_CFG3, MCP_20MHz_40kBPS_CFG3, MCP_20MHz_50kBPS_CFG3, MCP_20MHz_80kBPS_CFG3, MCP_20MHz_83k3BPS_CFG3, 0, MCP_20MHz_100kBPS_CFG3, MCP_20MHz_125kBPS_CFG3, MCP_20MHz_200kBPS_CFG3, MCP_20MHz_250kBPS_CFG3, MCP_20MHz_500kBPS_CFG3, MCP_20MHz_1000kBPS_CFG3}
	}
};

static const bool MCP_SPPED_VALID[3][16] {
	{true, true, true, true, true, true, true, true, false, false, true, true, true, true, true, true},
	{true, true, true, false, true, true, true, true, true, false, true, true, true, true, true, true},
	{false, false, false, false, true, true, true, true, true, false, true, true, true, true, true, true}
};




Mcp2515::Mcp2515(): mStatus(Status::CONFIGURATION) {
	Ldebug("MCP2515 inializaing...");

	mSpi.setBaudrate(5000000);
	this->reset();


}
Mcp2515::~Mcp2515() {}


void Mcp2515::reset() {
	uint8_t txBuf = 0xC0;
	mSpi.transfer(&txBuf, nullptr, 1);
	
	// read configruation
	uint8_t data = this->readRegister(0x0F);
	Ldebug("Register CANCTRL: %x", data);
	// data should be equal to 87...
	if (data != 0x87) throw string("configuration from MCP2515 invalid");
}


void Mcp2515::setConfigurationMode() {
	// write 0x87 to 0x0F
	this->writeRegister(0x0F, 0x87);

	mStatus = Status::CONFIGURATION;
}


void Mcp2515::setNormalMode() {
	this->modifyBit(0x0F, 0xE0, 0x00);
	uint8_t data = this->readRegister(0x0F);
	Ldebug("Register CANCTRL: %x", data);
	if ((data & 0xE0) != 0x00) throw string ("change mode to normal failed");
}

void Mcp2515::modifyBit(const uint8_t addr, const uint8_t mask, const uint8_t data) {
	uint8_t txBuf[4] {0x05, addr, mask, data};
	mSpi.transfer(txBuf, nullptr, 4);
}

void Mcp2515::setCanSpeed(CanSpeed speed) {
	this->setSpeed(MCP_8MHZ, speed);
}

void Mcp2515::setSpeed(McpClock mcpClock, CanSpeed speed) {
	if (mStatus != Status::CONFIGURATION) throw string("Mcp2515 not in configuration mode, cannot set");
	if (!MCP_SPPED_VALID[mcpClock][speed]) throw string("Mcp2515 not accept this speed configuration");

	uint8_t cfg1 = MCP_SPEED_CONFIG[0][mcpClock][speed];
	uint8_t cfg2 = MCP_SPEED_CONFIG[1][mcpClock][speed];
	uint8_t cfg3 = MCP_SPEED_CONFIG[2][mcpClock][speed];

	Ldebug("config: %x, %x, %x", cfg1, cfg2, cfg3);

	this->writeRegister(0x2A, cfg1);
	this->writeRegister(0x29, cfg2);
	this->writeRegister(0x28, cfg3);

	// read one by one
	int r1 = this->readRegister(0x2A);
	int r2 = this->readRegister(0x29);
	int r3 = this->readRegister(0x28);
	Ldebug("config in register: %x %x %x", r1, r2, r3);

	uint8_t r[3];
	this->readRegisters(0x28, r, 3);
	Ldebug("config in registers: %x %x %x", r[2], r[1], r[0]);

}


void Mcp2515::writeRegister(const uint8_t addr, const uint8_t data) {
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

void Mcp2515::readRegisters(const int8_t addr, uint8_t receive[], size_t len) {
	uint8_t *txBuf = new uint8_t[len+2];
	uint8_t *rxBuf = new uint8_t[len+2];
	memset(txBuf, 0, len+2);
	memset(rxBuf, 0, len+2);
	txBuf[0] = 0x03;
	txBuf[1] = addr;
	mSpi.transfer(txBuf, rxBuf, len+2);
	memcpy(receive, rxBuf+2, len);
	delete [] txBuf;
	delete [] rxBuf;
}


void Mcp2515::writeRegisters(const uint8_t addr, const uint8_t data[], size_t len) {
	uint8_t *txBuf = new uint8_t[len+2];
	uint8_t *rxBuf = new uint8_t[len+2];
	txBuf[0] = 0x02;
	txBuf[1] = addr;
	memcpy(txBuf+2, data, len);
	memset(rxBuf, 0, len+2);
	mSpi.transfer(txBuf, rxBuf, len+2);
	delete [] txBuf;
	delete [] rxBuf;	
}


void Mcp2515::sendMessage() {
	uint8_t txb0ctl = this->readRegister(0x30);

	uint8_t txreq = txb0ctl & (1<<3);
	Ldebug("txreq: %x", txreq);

	/*


	    byte res, res1, txbuf_n;
    uint16_t uiTimeOut = 0;

    can_id = id;
    ext_flg = ext;
    rtr = rtrBit;

    do {
        if (uiTimeOut > 0) {
            delayMicroseconds(10);
        }
        res = mcp2515_getNextFreeTXBuf(&txbuf_n);                       // info = addr.
        uiTimeOut++;
    } while (res == MCP_ALLTXBUSY && (uiTimeOut < TIMEOUTVALUE));

    if (uiTimeOut == TIMEOUTVALUE) {
        return CAN_GETTXBFTIMEOUT;                                      // get tx buff time out
    }
    mcp2515_write_canMsg(txbuf_n, id, ext, rtrBit, len, buf);

    if (wait_sent) {
        uiTimeOut = 0;
        do {
            if (uiTimeOut > 0) {
                delayMicroseconds(10);
            }
            uiTimeOut++;
            res1 = mcp2515_readRegister(txbuf_n - 1);  // read send buff ctrl reg
            res1 = res1 & 0x08;
        } while (res1 && (uiTimeOut < TIMEOUTVALUE));

        if (uiTimeOut == TIMEOUTVALUE) {                                     // send msg timeout
            return CAN_SENDMSGTIMEOUT;
        }
    }

    return CAN_OK;
		*/

}
