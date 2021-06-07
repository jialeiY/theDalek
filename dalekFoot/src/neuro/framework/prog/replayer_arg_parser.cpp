#include "framework/prog/replayer_arg_parser.h"
#include <getopt.h>
#include <string>

namespace framework {
namespace prog {

#ifndef NULL
#define NULL 0
#endif


namespace {
static struct option OPTION_CONFIG[] = {
	{"record-hardware", required_argument, NULL, 'h'},
	{NULL,              0,                 NULL,  0 }
};
}


ReplayerArgParser::ReplayerArgParser(int argc, char *argv[]) {
	while (true) {
		int optionVal = getopt_long(argc, argv, "h:", OPTION_CONFIG, NULL);
		if (-1 == optionVal) break;
		switch (optionVal) {
			case ('h'): {
				mHardwareRecordPath = std::string(optarg);
				break;
			}
			default: {
				break;
			}
		}
	}
}

ReplayerArgParser::~ReplayerArgParser() {

}

}
}