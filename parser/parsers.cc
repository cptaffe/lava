// Parsers

#include <stdlib.h>
#include <stdio.h>
#include "lava.h"
#include "parse.h"
#include "parsers.h"

namespace lava {

	void *Parser::parse_op(Lexeme *l) {
		if (l->typ == TYPE_ID) {
			printf("id '%s'\n", l->buf);
			return parse_all;
		} else {
			Err("unexpected type '%s' for '%s'", TypeString(l->typ)), TypeString(TYPE_ID));
			return parse_all;
		}
	}

	void *Parser::parse_all(Lexeme *l) {
		if (l->typ == TYPE_BP) {
			printf("list\n");
			parenDepth++;
			return parse_op;
		} else if (l->typ == TYPE_EP) {
			printf("end of list\n");
			parenDepth--;

			if (parenDepth == 0) {
				current = NULL;
				return parse_all;
			} else if (parenDepth < 0) {
				Err("extraneos ')'");
				current = NULL;
				return parse_all;
			}
		}

		return parse_all;
	}

}
