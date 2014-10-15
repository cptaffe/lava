#include <vector>
#include "types.h"

namespace lava {

	char *TypeString(int typ) {

		switch (typ) {
			case TYPE_BP:
				return (char *) "(";

			case TYPE_EP:
				return (char *) ")";

			case TYPE_ID:
				return (char *) "id";

			case TYPE_N:
				return (char *) "n";

			case TYPE_C:
				return (char *) "c";

			case TYPE_STR:
				return (char *) "str";

			default:
				return (char *) "unk";
		}
	}

	Obj::toString() {
		return TypeString(type);
	}

	Obj::Obj(int typ) {
		this->type = typ;
	}

	ObjTree::ObjTree(Obj *o, ObjTree *p) {
		self = o;
		parent = p;
		children = std::vector<ObjTree *>(); // presized for 10 children
	}

	ObjTree::~ObjTree() {
		delete children;
		delete self;
	}

}
