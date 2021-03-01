#include "ars4b.h"

#include <driver/mcp2515.h>
#include <utils/logger.h>

Ars4b::Ars4b() :mCan(nullptr) {
	mCan = new Mcp2515();
}



Ars4b::~Ars4b() {
	Ldebug("delete ARS-4B");
	delete mCan;
}
