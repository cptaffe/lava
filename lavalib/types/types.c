#include <stdlib.h>
#include "types.h"

char *type_str(int typ) {

	switch (typ) {
		case TYPE_BP:
			return "(";

		case TYPE_EP:
			return ")";

		case TYPE_ID:
			return "id";

		case TYPE_N:
			return "n";

		case TYPE_C:
			return "c";

		case TYPE_STR:
			return "str";

		default:
			return "unk";
	}
}

obj *make_obj(int type) {
	obj *o = malloc(sizeof(obj));
	o->type = type;
	return o;
}

obj_tree *make_obj_tree(obj *o, obj_tree *parent) {
	obj_tree *t = malloc(sizeof(obj_tree));
	t->self = (struct obj *) o;
	t->parent = parent;
	t->children = malloc(sizeof(obj_tree *) * OBJTREECHILDREN); // presized for 10 children
}

obj_tree *free_obj_tree(obj_tree *t) {
	free(t->children);
	free(t->self);
	free(t);
}
