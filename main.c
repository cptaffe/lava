#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lex.h"

int main() {
	lexer l = {.lexer = lex_all, .front = 0, .back = 0};
	l.buf = malloc(sizeof(char) * 100);
	l.que = malloc(sizeof(lexeme_que));
	l.que->top = 0;
	l.que->bottom = 0;
	l.que->que = malloc(sizeof(lexeme *) * 10);
	l.fd = open("test.lsp", O_RDONLY);
	l.len = read(l.fd, l.buf, LEXBUFF);
	lexeme *ret;

	while ((ret = ((lexeme *) lex(&l))) != NULL) {
		printf("got: '%s'\n", ret->buf);
	}

	return 0;
}
