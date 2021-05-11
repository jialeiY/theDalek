#include <iostream>

#include "framework/thread_hub.h"
#include "framework/timer_thread.h"
#include "framework/watchdog_thread.h"
#include "framework/io_thread.h"

using namespace std;

int main() {
	ThreadHub th;

	TimerThread tt(th);
	WatchdogThread wdt(th);
	IOThread iot(th);

	th.registerThread(&tt, "timer");
	th.registerThread(&wdt, "watchdog");
	th.registerThread(&iot, "io");

	wdt.start();
	iot.start();
	tt.start();

	while (true)
		;

	// char buffer[256];

	// while (true) {
	// 	int lenRead = read(ttyFd, buffer, 256);
	// 	for (int i=0; i<lenRead; ++i) {
	// 		// printf("%c", buffer[i]);
	// 	}
	// }

	return 0;
}