#include <vector>
#include <string>
#include <iostream>
#include "types.h"

namespace lava {

std::string TypeString(const int typ) {
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

	return "WTDKSDHFOSJFL";
}

std::string Obj::toString() {
	return TypeString(type);
}

Obj::Obj(int typ) {
	this->type = typ;
}

Obj::Obj(int typ, int num) {
	this->type = typ;
	this->num = num;
}

Obj::Obj(int typ, std::string *str) {
	this->type = typ;
	this->str = new std::string(*str);
}

Obj::Obj(int typ, char ch) {
	this->type = typ;
	this->ch = ch;
}

Obj::Obj(int typ, void *ptr) {
	this->type = typ;
	this->ptr = ptr;
}

ObjTree::ObjTree(Obj *o, ObjTree *p) {
	self = o;

	if (p != NULL) {
		p->AddChild(this);
	} else {
		parent = NULL;
	}

	this->children = new std::vector<ObjTree *>(); // presized for 10 children
}

ObjTree::~ObjTree() {
	for (std::vector<ObjTree *>::iterator it = children->begin(); it != children->end(); it++) {
		delete *it;
	}

	delete children;
	delete self;
}

ObjTree *ObjTree::AddChild(ObjTree *o) {
	if (o == NULL) { return o; }

	children->push_back(o);
	o->AddParent(this);
	return o;
}

void ObjTree::AddParent(ObjTree *o) {
	parent = o;
}

ObjTree *ObjTree::GetParent() {
	return parent;
}

std::string *ObjTree::toString() {
	std::string *str = new std::string();
	return this->toString(str);
}

std::string *ObjTree::toString(std::string *str) {
	if (self != NULL) {
		str->append(self->toString());
	}

	if (!children->empty()) {
		str->append("{");

		for (std::vector<ObjTree *>::iterator it = children->begin(); it != children->end(); it++) {
			(*it)->toString(str);

			if ((it + 1) != children->end()) {str->append(", ");}
		}

		str->append("}");
	}

	return str;
}

}
