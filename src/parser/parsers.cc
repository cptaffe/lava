// Parsers

#include <stdlib.h>
#include <stdio.h>
#include "lava.h"
#include "parse.h"
#include "parsers.h"

namespace lava {

void *parse_op(Parser *p, Lexeme *l) {
	if (l->typ == TYPE_ID) {
		printf("id '%s'\n", l->buf->c_str());
		return (void *) parse_all;
	} else {
		Err((char *) "unexpected type '%s' for '%s'", TypeString(l->typ).c_str(), 	TypeString(TYPE_ID).c_str());
		return (void *) parse_all;
	}
}

void *parse_all(Parser *p, Lexeme *l) {
	if (l->typ == TYPE_BP) {
		printf((char *) "list\n");
		p->parenDepth++;
		return (void *) parse_op;
	} else if (l->typ == TYPE_EP) {
		printf((char *) "end of list\n");
		p->parenDepth--;

		if (p->parenDepth == 0) {
			p->current = NULL;
			return (void *) parse_all;
		} else if (p->parenDepth < 0) {
			Err((char *) "extraneos ')'");
			p->current = NULL;
			return (void *) parse_all;
		}
	}

	return (void *) parse_all;
}

}
