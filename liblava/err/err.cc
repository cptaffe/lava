// Errors

#include <stdio.h>
#include <stdarg.h>

namespace lava {

	// simple errors
	int Err(char *str, ...) {
		va_list vl;
		va_start(vl, str);
		fprintf(stderr, "err: ");
		int res = vfprintf(stderr, str, vl);
		va_end(vl);
		printf("\n");
		return res;
	}

}
