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

	//printf("opening '%s'\n", argc[1]);

	int fd = open(argc[1], O_RDONLY);
	if (fd < 0) {
		printf("cannot open '%s'\n", argc[1]);
		exit(1);
	}
	lexer *l = make_lexer(fd);
	parser p = {.parser = parse_all, .parenDepth = 0};
	obj_tree *pr = make_obj_tree(NULL, NULL);
	p.root = pr;
	p.current = pr;

	// parses one statement
	lexeme *lexeme;
	while ((lexeme = lex(l)) != NULL) {
		parse(&p, lexeme);
	}

	printf("\n");
	free_lexer(l);
	free_obj_tree(p.root);
}
