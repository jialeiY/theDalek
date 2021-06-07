#ifndef __MODULE_DATA_TYPES_QUALIFIER_H__
#define __MODULE_DATA_TYPES_QUALIFIER_H__

#include <cstdint>
#include <string>

namespace data_types {

constexpr const char * QUALIFIER_READ_ERROR_STR {"QUALIFIER_READ_ERROR"};
constexpr const char * QUALIFIER_READ_OK_STR {"QUALIFIER_READ_OK"};
constexpr const char * QUALIFIER_ERROR_ID_STR {"QUALIFIER_ERROR_ID"};
constexpr const char * QUALIFIER_ERROR_NOT_READY_STR {"QUALIFIER_ERROR_NOT_READY"};

enum Qualifier : std::uint8_t {
	QUALIFIER_READ_ERROR = 0,
	QUALIFIER_READ_OK = 1,
	QUALIFIER_ERROR_NOT_READY = 2,
	QUALIFIER_ERROR_FAILSAFE = 3
};

static inline std::string toString(const enum Qualifier &qualifier) {
	switch (qualifier) {
		case (QUALIFIER_READ_ERROR): {
			return QUALIFIER_READ_ERROR_STR;
		}
		case (QUALIFIER_READ_OK): {
			return QUALIFIER_READ_OK_STR;
		}
		case (QUALIFIER_ERROR_NOT_READY): {
			return QUALIFIER_ERROR_NOT_READY_STR;
		}
		default: {
			return QUALIFIER_ERROR_ID_STR;
		}
	}
}

}




#endif


