#include <vector>
#include <string>
#include "types.h"

namespace lava {

	std::string TypeString(int typ) {

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

	std::string Obj::toString() {
		return TypeString(type);
	}

	Obj::Obj(int typ) {
		this->type = typ;
	}

	ObjTree::ObjTree(Obj *o, ObjTree *p) {
		self = o;
		parent = p;
		children = new std::vector<ObjTree *>(); // presized for 10 children
	}

	ObjTree::~ObjTree() {
		// delete children;
		delete self;
	}

}
