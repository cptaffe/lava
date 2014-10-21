#include <vector>
#include <string>
#include <iostream>
#include "types/types.h"
#include "keywords/keywords.h"

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

// Obj utilities
std::string Obj::toString() {
	return TypeString(type);
}

// is obj an id?
bool Obj::isId() {
	return type == TYPE_ID;
}

// is obj an num?
bool Obj::isNum() {
	return type == TYPE_N;
}

// is id a keyword?
bool Obj::isBuiltin() {
	if (str->compare(KEYWORD_ADD) == 0 || str->compare(KEYWORD_SUB) == 0 || str->compare(KEYWORD_MUL) == 0 || str->compare(KEYWORD_DIV) == 0) {return true;}
	else {return false;}
}

Obj::Obj(int typ) {
	this->type = typ;
	this->str = NULL;
}

Obj::Obj(int typ, int num) {
	this->type = typ;
	this->str = NULL;
	this->num = num;
}

Obj::Obj(int typ, std::string *str) {
	this->type = typ;
	this->str = str;
}

Obj::Obj(int typ, char ch) {
	this->type = typ;
	this->ch = ch;
	this->str = NULL;
}

Obj::Obj(int typ, void *ptr) {
	this->type = typ;
	this->ptr = ptr;
	this->str = NULL;
}

Obj::~Obj() {
	if (str != NULL) {
		delete str;
	}
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

std::string *ObjTree::toString() const {
	std::string *str = new std::string();
	return toString(str);
}

std::string *ObjTree::toString(std::string *str) const {
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

ObjVar::ObjVar(std::string *str, Obj *obj) {
	this->name = new std::string(*str);
	this->obj = obj;
}

ObjVar::~ObjVar() {
	delete name;
}

}
