#ifndef __MODULE_DATA_TYPES_QUALIFIER_H__
#define __MODULE_DATA_TYPES_QUALIFIER_H__

#include <cstdint>

namespace data_types {

enum Qualifier : std::uint8_t {
	QUALIFIER_READ_ERROR = 0,
	QUALIFIER_READ_OK = 1
};

}




#endif


