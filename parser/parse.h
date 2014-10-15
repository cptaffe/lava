// Parser interface

// The parser takes lexemes, creates their associated object,
// and puts them in a tree.

#ifndef PARSE_H
#define PARSE_H

#include "lava.h"
#include "lexeme.h"

namespace lava {

	class Parser {
		int parenDepth; // up & down tree
		ObjTree *root;
		ObjTree *current;
		void *parser;
	public:
		Parser();
		~Parser();
		ObjTree *parse(Lexeme *);
		void *parse_all(Lexeme *)
	};

	typedef void *(Parser::*ParseFunc)(Lexeme *);

}

#endif
