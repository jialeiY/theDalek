#include <iostream>
#include <unistd.h>
using namespace std;

#include <utils/logger.h>

#include "sensor/ars4b.h"



int main(void) {
	try {
		Radar *ars = new Ars4b();

		usleep(1000ULL*1000ULL);
		ars->work();
		while (false) {
			usleep(1000ULL*1000ULL);
			ars->work();
		}



		delete ars;
	} catch (string e) {
		Lerror("%s", e.c_str());
	} catch (const char * e) {
		Lerror("%s", e);
	}

	
	
	return 0;
}