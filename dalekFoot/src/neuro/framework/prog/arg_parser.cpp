#include "framework/prog/arg_parser.h"
#include <getopt.h>
#include <string>

namespace framework {
namespace prog {

#ifndef NULL
#define NULL 0
#endif


namespace {
static struct option OPTION_CONFIG[] = {
	{"record-hardware-output", required_argument, NULL, 'h'},
	{"record-all-output",      required_argument, NULL, 'a'},
	{NULL,              0,                 NULL,  0 }
};
}


ArgParser::ArgParser(int argc, char *argv[]) {
	while (true) {
		int optionVal = getopt_long(argc, argv, "h:a:", OPTION_CONFIG, NULL);
		if (-1 == optionVal) break;
		switch (optionVal) {
			case ('h'): {
				mHardwareRecordOutputPath = std::string(optarg);
				break;
			}
			case ('a'): {
				mAllRecordOutputPath = std::string(optarg);
				break;
			}
			default: {
				break;
			}
		}
	}
}

ArgParser::~ArgParser() {

}

}
}