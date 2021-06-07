#ifndef __FRAMEWORK_PROG_REPLAYER_ARG_PARSER_H__
#define __FRAMEWORK_PROG_REPLAYER_ARG_PARSER_H__

#include <string>

namespace framework {
namespace prog {




class ReplayerArgParser {
	public:
		ReplayerArgParser(int argc, char *argv[]);
		virtual ~ReplayerArgParser();
		std::string getHardwareRecordPath(void) const {return mHardwareRecordPath;}
	private:
		std::string mHardwareRecordPath;
};
	

}
}


#endif

