#include <stdlib.h>
#include <stdio.h>
#include "lava.h"
#include "parse.h"

namespace lava {

	Parser::Parser() {
		parenDepth = 0;
		root = new ObjTree(NULL, NULL);
		current = root;
		parser = (void *) parse_all;
	}

	Parser::~Parser() {
		delete root;
	}

	// Takes lexeme and builds tree, saves state between calls.
	// Returns NULL until a full tree has been built, then returns tree.
	ObjTree *Parser::parse(Lexeme *l) {
		if (l == NULL) {
			delete l;
			return root;
		} // assume eof, bail.

		if (parser != NULL) {
			parser = ((ParseFunc) parser)(this, l);

			if (current == NULL) {
				delete l;
				return root;
			}
		}

		delete l;
		return NULL;
	}

}
