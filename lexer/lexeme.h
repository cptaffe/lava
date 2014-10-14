
#ifndef LEXEME_H
#define LEXEME_H

#include "lava.h"

// lexeme returned to the caller
typedef struct {
	char *buf;
	int typ;
} lexeme;

lexeme *make_lexeme(int typ, char *buf);
void free_lexeme(lexeme *l);

#endif
