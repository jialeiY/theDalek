#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cstring>
#include "module/data_types/hardware_data.h"
#include "framework/prog/replayer_arg_parser.h"


int main(int argc, char *argv[], char *env[]) {
	framework::prog::ReplayerArgParser ap(argc, argv);
	FILE *hardwareRecordFile = fopen(ap.getHardwareRecordPath().c_str(), "rb");
	if (hardwareRecordFile == nullptr) {
		printf("error loading record file: %s\r\n", ap.getHardwareRecordPath().c_str());
		exit(1);
	}

	constexpr std::size_t hardwareSize {sizeof(data_types::HardwareData)};

	std::uint8_t buffer[hardwareSize];
	
	while (true) {
		std::cout << "Press Enter to Continue";
		// std::cin.ignore();
		std::size_t len = fread(buffer, hardwareSize, 1, hardwareRecordFile);
		if (len < 1) break;
		std::cout << len << std::endl;

		data_types::HardwareData data;
		memcpy(&data, buffer, hardwareSize);
		std::cout << "input time: " << data.input.cycleStartTime 
			<< "  encoder: " << data.input.mcuSensors.motorEncoder[3]
			<< "  qualifier: " << toString(data.input.mcuSensors.qualifier) << std::endl;
	}


	return 0;
}