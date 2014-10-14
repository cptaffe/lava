// Lexeme functions

#include "lexeme.h"
#include <stdlib.h>

lexeme *make_lexeme(int typ, char *buf) {
	lexeme *lex = malloc(sizeof(lexeme));
	lex->typ = typ;
	lex->buf = buf;
	return lex;
}

void free_lexeme(lexeme *l) {
	free(l->buf);
	free(l);
}
