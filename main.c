#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lexer/lex.h"
#include "parser/parse.h"

int main(int argv, char *argc[]) {
	if (argv < 2) {
		printf("need file name\n");
		exit(1);
	}
	lexer l = {.lexer = lex_all, .front = 0, .back = 0};
	l.buf = malloc(sizeof(char) * 100);
	l.que = malloc(sizeof(lexeme_que));
	l.que->top = 0;
	l.que->bottom = 0;
	l.que->que = malloc(sizeof(lexeme *) * 10);
	l.fd = open(argc[1], O_RDONLY);
	if (l.fd < 0) {
		printf("cannot open '%s'\n", argc[1]);
		exit(1);
	}
	l.len = read(l.fd, l.buf, LEXBUFF);
	parser p = {.parser = parse_all, .parenDepth = 0};
	obj_tree pr = {.tree = NULL, .child = NULL};
	p.root = &pr;
	p.current = &pr;

	// parses one statement
	while (parse(&p, lex(&l)) == NULL) {}

	printf("\n");
	free(l.buf);
	free(l.que->que);
	free(l.que);
	return 0;
}
