// Parsers

#include <stdlib.h>
#include <stdio.h>
#include "../lavalib/lava.h"
#include "parse.h"
#include "parsers.h"

void *parse_op(parser *p, lexeme *l) {
	if (l->typ == TYPE_ID) {
		return parse_all;
	} else {
		lava_err("unexpected type '%s' for '%s'", type_str(l->typ), type_str(TYPE_ID));
		return parse_all;
	}
}

void *parse_all(parser *p, lexeme *l) {
	if (l->typ == TYPE_BP) {
		printf("{");
		p->parenDepth++;
		return parse_op;
	} else if (l->typ == TYPE_EP) {
		printf("}");
		p->parenDepth--;

		if (p->parenDepth == 0) {
			p->current = NULL;
			return parse_all;
		} else if (p->parenDepth < 0) {
			lava_err("extraneos ')'");
			p->current = NULL;
			return parse_all;
		}
	}

	return parse_all;
}
