#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

void *parse_all(parser *p, lexeme *l) {
	printf("%s, ", l->buf);
	return parse_all;
}

// Takes lexeme and builds tree, saves state between calls.
// Returns NULL until a full tree has been built, then returns tree.
obj_tree *parse(parser *p, lexeme *l) {
	if (p->parser != NULL) {
		p->parser = ((parse_func) p->parser)(p, l);
		if (p->current == NULL) {return p->root;}
	}
	return NULL;
}
