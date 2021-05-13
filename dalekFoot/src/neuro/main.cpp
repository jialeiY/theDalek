#include <iostream>
#include <string>
#include <vector>
#include "framework/thread_hub.h"
#include "framework/timer_thread.h"
#include "framework/watchdog_thread.h"
#include "framework/io_thread.h"
#include <numeric>

using namespace std;


vector<string> splitString(const string &str) {
	vector<string> ret;
	size_t found = string::npos;
	size_t last = 0;
	while ((found = str.find(' ', last)) != std::string::npos) {
    ret.push_back(move(str.substr(last, (found - last))));
		last = found + 1;
	}
	ret.push_back(str.substr(last, str.size() - last));
	return ret;
}

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

	string cmd;

	while (true) {
		getline(cin, cmd);
		vector<string> cmdList = splitString(cmd);
		string out = accumulate(next(begin(cmdList)), end(cmdList), cmdList.front(), [](string acc, const string &item) {
			return acc + " - " + item;
		});
		cout << out << endl;		

	}
		

	// char buffer[256];

	// while (true) {
	// 	int lenRead = read(ttyFd, buffer, 256);
	// 	for (int i=0; i<lenRead; ++i) {
	// 		// printf("%c", buffer[i]);
	// 	}
	// }

	return 0;
}