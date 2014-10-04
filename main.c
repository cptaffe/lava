#include <stdio.h>
#include "lex.h"

int main() {
	lexer l = {.lexer = lexAll, .pos = 0};
	lexeme_que que = {0};
	char buf[LEXBUFF];
	l.buf = (char *) &buf;
	l.que = &que;
	l.fd = open("test.lsp", O_RDONLY);
	l.len = read(l.fd, &l.buf, LEXBUFF);
	printf("%p\n", lex(&l));
}