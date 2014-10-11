#include <stdlib.h>
#include <stdio.h>
#include "../lavalib/lava.h"
#include "parse.h"

// Takes lexeme and builds tree, saves state between calls.
// Returns NULL until a full tree has been built, then returns tree.
obj_tree *parse(parser *p, lexeme *l) {
	if (l == NULL) {
		lexeme_destroy(l);
		return p->root;
	} // assume eof, bail.

	if (p->parser != NULL) {
		p->parser = ((parse_func) p->parser)(p, l);

		if (p->current == NULL) {
			lexeme_destroy(l);
			return p->root;
		}
	}

	lexeme_destroy(l);
	return NULL;
}
