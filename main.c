#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

int main() {
	lexer l = {.lexer = lex_all, .pos = 0};
	lexeme_que que = {0};
	int buf[LEXBUFF];
	l.buf = (char *) &buf;
	l.que = &que;
	lexeme *que2[10];
	l.que->que = (lexeme **) &que2;
	l.fd = open("test.lsp", O_RDONLY);
	l.len = read(l.fd, &l.buf, LEXBUFF);
	printf("%s\n", ((lexeme *) lex(&l))->buf);
	return 0;
}