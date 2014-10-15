#include <stdlib.h>
#include <stdio.h>
#include "lava.h"
#include "parse.h"

namespace lava {

	Parser::Parser() {
		parenDepth = 0;
		ObjTree root = new ObjTree;
		ObjTree current = root;
		parser = parse_all;
	}

	// Takes lexeme and builds tree, saves state between calls.
	// Returns NULL until a full tree has been built, then returns tree.
	ObjTree *Parser::parse(lexeme *l) {
		if (l == NULL) {
			delete l;
			return root;
		} // assume eof, bail.

		if (parser != NULL) {
			parser = ((ParseFunc) *this:*parser)(l);

			if (current == NULL) {
				delete l;
				return root;
			}
		}

		delete l;
		return NULL;
	}

}
