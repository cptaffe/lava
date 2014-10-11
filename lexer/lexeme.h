
#ifndef LEXEME_H
#define LEXEME_H

#include "../lavalib/lava.h"

// lexeme returned to the caller
typedef struct {
	char *buf;
	int typ;
} lexeme;

lexeme *make_lexeme(int typ, char *buf);
int lexeme_destroy(lexeme *l);

#endif
