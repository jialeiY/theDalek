#include "ars4b.h"

#include <driver/mcp2515.h>
#include <utils/logger.h>

Ars4b::Ars4b() :mCan(nullptr) {
	Mcp2515 *mcp = new Mcp2515();
	mcp->setCanSpeed(Can::CAN_500KBPS);
	mcp->setNormalMode();
	mCan = mcp;
}



Ars4b::~Ars4b() {
	Ldebug("delete ARS-4B");
	delete mCan;
}
