
#ifndef LEXEME_H
#define LEXEME_H

#include "../types.h"

// lexeme returned to the caller
typedef struct {
	char *buf;
	int typ;
} lexeme;

#endif