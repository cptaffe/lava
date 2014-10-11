// Errors

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int lava_err(char *str, ...) {
	va_list vl;
	va_start(vl, str);
	fprintf(stderr, "err: ");
	int res = vfprintf(stderr, str, vl);
	va_end(vl);
	printf("\n");
	return res;
}
