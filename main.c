#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lexer/lex.h"
#include "parser/parse.h"

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

	parser p = {.parser = parse_all};
	obj_tree pr = {.tree = NULL, .child = NULL};
	obj_tree pc = {.tree = NULL, .child = NULL};
	p.root = &pr;
	p.current = &pc;

	while ((ret = lex(&l)) != NULL) {
		parse(&p, ret);
	}
	printf("\n");

	return 0;
}
