#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "lava.h"
#include "lex.h"
#include "parse.h"

int main(int argv, char *argc[]) {
	if (argv < 2) {
		std::cout << "need file name" << std::endl;
		return 1;
	}

	int fd = open(argc[1], O_RDONLY);

	if (fd < 0) {
		std::cout << "cannot open " << "'" << argc[1] << "'" << std::endl;
		return 1;
	}

	lava::Lexer *l = new lava::Lexer(fd);
	lava::Parser *p = new lava::Parser();
	// parses one statement
	lava::Lexeme *lexeme;

	while ((lexeme = l->lex()) != NULL) {
		lava::ObjTree *obj = p->parse(lexeme);

		if (obj != NULL) {
			std::cout << *obj->toString() << std::endl;
		}
	}

	delete l;
	delete p;
}
