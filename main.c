#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lava.h"
#include "lex.h"
#include "parse.h"

int main(int argv, char *argc[]) {
	if (argv < 2) {
		printf("need file name\n");
		exit(1);
	}

	//printf("opening '%s'\n", argc[1]);

	int fd = open(argc[1], O_RDONLY);
	if (fd < 0) {
		printf("cannot open '%s'\n", argc[1]);
		exit(1);
	}
	printf("open suceeded\n");
	lexer *l = make_lexer(fd);
	printf("make_lexer suceeded.\n");
	parser p = {.parser = parse_all, .parenDepth = 0};
	obj_tree *pr = make_obj_tree(NULL, NULL);
	printf("make_obj_tree suceeded.\n");
	p.root = pr;
	p.current = pr;

	// parses one statement
	lexeme *lexeme;
	printf("beginning parse loop.\n");
	while ((lexeme = lex(l)) != NULL) {
		printf("parse lexeme '%s'\n", lexeme->buf);
		parse(&p, lexeme);
	}
	printf("parse loop sucess\n");

	printf("\n");
	free_lexer(l);
	free_obj_tree(p.root);
}
