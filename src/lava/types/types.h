// Defines types

#ifndef LAVA_LAVA_TYPES_TYPES_H_
#define LAVA_LAVA_TYPES_TYPES_H_

#include <string>
#include <vector>

namespace lava {

// types
enum {
	TYPE_BP = 0, // begenning paren
	TYPE_EP, // ending paren
	TYPE_ID,
	TYPE_N, // number literal
	TYPE_C, // character literal
	TYPE_STR // string literal
};

// The Object type
class Obj {
public:
	int type;
	union {
		// number (64 bit)
		long long int num;
		// string
		std::string *str;
		// character
		char ch;
		// pointer
		void *ptr; // ids should point to symbol table
	};
	Obj(int);
	Obj(int, int);
	Obj(int, std::string *);
	Obj(int, char);
	Obj(int, void *);
	std::string toString();
};

// Abstract Syntax Tree
class ObjTree {
public:
	Obj *self;
	ObjTree *parent;
	std::vector<ObjTree *> *children; // array
	ObjTree(Obj *, ObjTree *);
	~ObjTree();
	ObjTree *AddChild(ObjTree *);
	ObjTree *GetParent();
	std::string *toString();
private:
	std::string *toString(std::string *str);
	void AddParent(ObjTree *);
};

// Object storage: name & ptr to Obj
class ObjVar {
	std::string *name;
	Obj *obj;
public:
	ObjVar(std::string *, Obj *);
	~ObjVar();
};

std::string TypeString(const int typ);

}

#endif // LAVA_LAVA_TYPES_TYPES_H_
