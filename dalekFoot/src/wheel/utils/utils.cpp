#include "utils.hpp"

extern volatile uint32_t gMillis;
namespace System {
	



uint32_t millis() {
	return gMillis;
}

}