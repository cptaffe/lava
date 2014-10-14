#include <stdlib.h>
#include <stdio.h>
#include "lava.h"
#include "parse.h"

// Takes lexeme and builds tree, saves state between calls.
// Returns NULL until a full tree has been built, then returns tree.
obj_tree *parse(parser *p, lexeme *l) {
	if (l == NULL) {
		free_lexeme(l);
		return p->root;
	} // assume eof, bail.

	if (p->parser != NULL) {
		p->parser = ((parse_func) p->parser)(p, l);

		if (p->current == NULL) {
			free_lexeme(l);
			return p->root;
		}
	}

	free_lexeme(l);
	return NULL;
}
