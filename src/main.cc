#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "lava.h"
#include "lex.h"
#include "parse.h"

int main(int argv, char *argc[]) {
	if (argv < 2) {
		printf("need file name\n");
		exit(1);
	}

	int fd = open(argc[1], O_RDONLY);
	if (fd < 0) {
		printf("cannot open '%s'\n", argc[1]);
		exit(1);
	}
	lava::Lexer *l = new lava::Lexer(fd);
	lava::Parser *p = new lava::Parser();

	// parses one statement
	lava::Lexeme *lexeme;

	while ((lexeme = l->lex()) != NULL) {
		p->parse(lexeme);
		//std::cout << "lex: " << "'" << lexeme->buf->c_str() << "'" << std::endl;
	}

	delete l;
	delete p;
}
