// Parsers
#include <string>
#include "lava.h"
#include "parse.h"
#include "parsers.h"

namespace lava {

void *parse_op(Parser *p, Lexeme *l) {
	if (l->typ == TYPE_ID) {
		p->current = new ObjTree(new Obj(l->typ, l->buf), p->current); // attaches to current as child
		return (void *) parse_ops;
	} else {
		Err((char *) "unexpected type '%s' for '%s'", TypeString(l->typ).c_str(), 	TypeString(TYPE_ID).c_str());
		return (void *) parse_all;
	}
}

void *parse_ops(Parser *p, Lexeme *l) {
	if (l->typ == TYPE_ID) {
		new ObjTree(new Obj(l->typ, l->buf), p->current); // attaches to current as child
		return (void *) parse_ops;
	} else if (l->typ == TYPE_N) {
		new ObjTree(new Obj(l->typ, std::stoi(*l->buf)), p->current); // attaches to current as child
		return (void *) parse_ops;
	} else {
		return parse_all(p, l); // pass current lexeme to parse_all
	}
}

void *parse_all(Parser *p, Lexeme *l) {
	if (l->typ == TYPE_BP) {
		p->parenDepth++;
		// p->current = new ObjTree(new Obj(TYPE_BP), p->current);
		return (void *) parse_op;
	} else if (l->typ == TYPE_EP) {
		p->parenDepth--;
		p->current = p->current->GetParent(); // go up a level

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
