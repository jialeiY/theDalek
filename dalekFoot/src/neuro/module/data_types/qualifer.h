#ifndef __MODULE_DATA_TYPES_QUALIFIER_H__
#define __MODULE_DATA_TYPES_QUALIFIER_H__

#include <cstdint>
#include <string>

namespace data_types {

constexpr const char * QUALIFIER_READ_ERROR_STR {"QUALIFIER_READ_ERROR"};
constexpr const char * QUALIFIER_READ_OK_STR {"QUALIFIER_READ_OK"};
constexpr const char * QUALIFIER_ERROR_ID_STR {"QUALIFIER_ERROR_ID"};
enum Qualifier : std::uint8_t {
	QUALIFIER_READ_ERROR = 0,
	QUALIFIER_READ_OK = 1
};

static inline std::string toString(const enum Qualifier &qualifier) {
	switch (qualifier) {
		case (QUALIFIER_READ_ERROR): {
			return QUALIFIER_READ_ERROR_STR;
		}
		case (QUALIFIER_READ_OK): {
			return QUALIFIER_READ_OK_STR;
		}
		default: {
			return QUALIFIER_ERROR_ID_STR;
		}
	}
}

}




#endif


