#include "lava.h"
#include "parse.h"

namespace lava {

Parser::Parser(lava::que<Lexeme *> *que) {
	parenDepth = 0;
	root = new ObjTree(NULL, NULL);
	current = root;
	this->que = que;
	objs = new lava::que<ObjTree *>();
	parser = (void *) parse_all;
}

Parser::~Parser() {
	delete root;
	delete objs;
}

// Takes lexeme and builds tree, saves state between calls.
// Returns NULL until a full tree has been built, then returns tree.
void Parser::parse() {

	while (true) {
		while (current != NULL) {
			Lexeme *l;
			que->pop(l);

			if (l == NULL) {
				delete l;
				objs->push(root);
				root = new ObjTree(NULL, NULL);
				current = root;
				objs->finish();
				return;
			} // assume eof, bail.

			if (parser != NULL) {
				parser = ((ParseFunc) parser)(this, l);
			}

			delete l;
		}

		// when current is null
		objs->push(root);
		root = new ObjTree(NULL, NULL);
		current = root;
	}
}

}
