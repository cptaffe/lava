// Parser interface

// The parser takes lexemes, creates their associated object,
// and puts them in a tree.

#ifndef PARSE_H
#define PARSE_H

#include "lava.h"
#include "lexeme.h"

namespace lava {

	class Parser {
	public:
		int parenDepth; // up & down tree
		ObjTree *root;
		ObjTree *current;
		void *parser;
		Parser();
		~Parser();
		ObjTree *parse(Lexeme *);
	};

	typedef void *(*ParseFunc)(Parser *, Lexeme *);

	void *parse_all(Parser *p, Lexeme *l);

}

#endif
