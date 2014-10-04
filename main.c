#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

int main() {
	lexer l = {.lexer = lex_all, .pos = 0};
	lexeme_que que = {0};
	l.buf = malloc(LEXBUFF * sizeof(char *));
	l.que = &que;
	l.que->que = malloc(10 * sizeof(lexeme *));
	l.fd = open("test.lsp", O_RDONLY);
	l.len = read(l.fd, &l.buf, LEXBUFF);
	printf("%s\n", ((lexeme *) lex(&l))->buf);
	//free(l.buf);
	//free(l.que->que);
}