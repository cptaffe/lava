// Parser interface

// The parser takes lexemes, creates their associated object,
// and puts them in a tree.

#ifndef PARSE_H
#define PARSE_H

#include "../lavalib/lava.h"
#include "../lexer/lexeme.h"

typedef struct {
	int parenDepth; // up & down tree
	obj_tree *root;
	obj_tree *current;
	void *parser;
} parser;

typedef void *(* parse_func)(parser *, lexeme *);

obj_tree *parse(parser *p, lexeme *l);
void *parse_all(parser *p, lexeme *l);

#endif
