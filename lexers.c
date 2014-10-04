// Lexers.c
// contains all lexers

#include <stdlib.h>
#include <stdio.h> // debug
#include <unistd.h>
#include "lex.h"

lexeme *make_lexeme(int typ, char *buf) {
	lexeme *lex = malloc(sizeof(lexeme));
	lex->typ = typ;
	lex->buf = buf;
	return lex;
}

void *lex_all(lexer *l) {
	write(1, &l->buf, l->len);
	printf("%p\n", l->buf);
	//if (l->buf == '(') {
		lex_que_push(l->que, make_lexeme(1, ")"));
	//}
	return lex_all;
}