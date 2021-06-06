#include <cstdio>
#include <cstdint>
#include <iostream>
#include <limits>
#include <cstring>
#include "module/data_types/hardware_data.h"


int main(int argc, char *argv[], char *env[]) {
	FILE *hardwareRecordFile = fopen("runtime/hardware.dat", "rb");
	constexpr std::size_t hardwareSize {sizeof(data_types::HardwareData)};

	std::uint8_t buffer[hardwareSize];
	
	while (true) {
		std::cout << "Press Enter to Continue";
		std::cin.ignore();
		std::size_t len = fread(buffer, hardwareSize, 1, hardwareRecordFile);
		if (len < 1) break;
		std::cout << len << std::endl;

		data_types::HardwareData data;
		memcpy(&data, buffer, hardwareSize);
		std::cout << "input time: " << data.input.cycleStartTime << std::endl;
	}


	return 0;
}