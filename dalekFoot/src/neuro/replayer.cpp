#include "replayer.h"
#include "module/data_types/hardware_data.h"
#include "framework/prog/replayer_arg_parser.h"
#include "framework/thread/entity_agency.h"
#include "module/sensing/wheel_sensor/wheel_sensor.h"
#include "action/power/power_action.h"
#include "action/odometry/odometry_action.h"
#include "framework/thread/control/controller.h"
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cstring>


int main(int argc, char *argv[], char *env[]) {
	framework::prog::ReplayerArgParser ap(argc, argv);
	FILE *hardwareRecordFile = fopen(ap.getHardwareRecordPath().c_str(), "rb");
	if (hardwareRecordFile == nullptr) {
		printf("error loading record file: %s\r\n", ap.getHardwareRecordPath().c_str());
		exit(1);
	}
	constexpr std::size_t hardwareSize {sizeof(data_types::HardwareData)};
	std::uint8_t buffer[hardwareSize];
	
	
	framework::thread::EntityAgency ea;
	// setup hardware
	sensing::wheel_sensor::WheelSensor wheelSensor("wheel", ea);
	// setup action
	action::power::PowerAction power("power", ea);
	action::odometry::OdometryAction odometry("odometry", ea);
	framework::thread::control::Controller controller(ea);
	controller.init();

	
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

		controller.step(&data);

		std::cout << "output: [" << (int)(data.output.value) << "]" << std::endl;

	}


	return 0;
}

