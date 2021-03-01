#include <iostream>
using namespace std;

#include <utils/logger.h>

#include "sensor/ars4b.h"



int main(void) {
	try {
		Radar *ars4b = new Ars4b();
		delete ars4b;
	} catch (string e) {
		Lerror("%s", e.c_str());
	} catch (const char * e) {
		Lerror("%s", e);
	}

	
	
	return 0;
}