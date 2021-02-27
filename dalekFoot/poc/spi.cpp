//#include <json.hpp>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

using namespace std;
//using namespace nlohmann;

int main(void) {
//	json config;
//	ifstream confFile("conf.json", ifstream::binary);
//	confFile >> config;
//	cout << config["device"] << endl;
	string device = "/dev/spidev0.0";


	return 0;
}

