// Errors

#include <iostream>
#include "err/err.h"

namespace lava {

Err err;

Err::Err() {
	out = &std::cerr;
}

}
