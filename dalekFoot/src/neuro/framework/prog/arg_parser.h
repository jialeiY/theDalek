#ifndef __FRAMEWORK_PROG_ARG_PARSER_H__
#define __FRAMEWORK_PROG_ARG_PARSER_H__

#include <string>

namespace framework {
namespace prog {




class ArgParser {
	public:
		ArgParser(int argc, char *argv[]);
		virtual ~ArgParser();
		std::string getHardwareOutput(void) const {return mHardwareRecordOutputPath;}
		std::string getAllOutput(void) const {return mAllRecordOutputPath;}
	private:
		std::string mHardwareRecordOutputPath;
		std::string mAllRecordOutputPath;
};
	

}
}


#endif

