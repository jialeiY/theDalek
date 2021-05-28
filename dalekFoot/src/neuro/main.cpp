#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "framework/thread_hub.h"
#include "framework/loop_thread.h"
#include "framework/control_thread.h"
#include <numeric>

#include "framework/entity_agency.h"

#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "action/power/power_action.h"
#include "action/odometry/odometry_action.h"


using namespace std;


vector<string> splitString(const string &str) {
	vector<string> ret;
	size_t last = 0;

	for (int i=0; i<str.size(); ++i) {
		if (str[i] == ' ') {
			if (i - last > 0) {
				ret.push_back(str.substr(last, i-last));
			}
			last = i + 1;
		}
	}
	if (str.size() - last > 0) {
		ret.push_back(str.substr(last, str.size() - last));
	}
	return ret;
}
extern volatile uint8_t m4speed;
int main() {
	framework::EntityAgency ea;
	
	// setup hardware
	sensing::wheel_sensor::WheelSensor wheelSensor("wheel", ea);
	
	// setup action
	action::power::PowerAction power("power", ea);
	action::odometry::OdometryAction odometry("odometry", ea);

	// setup application

	// start program


	framework::ThreadHub th;
	framework::LoopThread lt(th);
	framework::ControlThread ct(th, ea);

	th.registerThread(&lt, "loop");
	th.registerThread(&ct, "control");
	
	lt.init();
	ct.init();

	lt.start();
	ct.start();



	
	// string cmd;

	// while (true) {
	// 	cout << "cmd > " << flush;
	// 	getline(cin, cmd);
	// 	vector<string> cmdList = splitString(cmd);
	// 	vector<string> cleanCmdList;
	// 	std::copy_if(cmdList.begin(), cmdList.end(), std::back_inserter(cleanCmdList), [](const string &str) {
	// 		return str.size() > 0;
	// 	});

	// 	if (cmdList.size() < 1) continue;
		

	// 	string out = accumulate(next(begin(cleanCmdList)), end(cleanCmdList), cleanCmdList.front(), [](string acc, const string &item) {
	// 		return acc + " - " + item;
	// 	});
	// 	cout << out << endl;


	// 	if (cleanCmdList[0] == "quit" || cleanCmdList[0] == "q") {
	// 		break;
	// 	}
		
	// 	if (cleanCmdList[0] == "m4") {
	// 		if (cleanCmdList.size() < 3) continue;
	// 		if (cleanCmdList[1] == "set") {
	// 			int speed = atoi(cleanCmdList[2].c_str());
	// 			cout << "set motor 4 speed to " << speed << endl;
	// 			m4speed = speed;
	// 		}
	// 	}
	// }
	

	// char buffer[256];

	// while (true) {
	// 	int lenRead = read(ttyFd, buffer, 256);
	// 	for (int i=0; i<lenRead; ++i) {
	// 		// printf("%c", buffer[i]);
	// 	}
	// }

	while (true);

	return 0;
}