// Defines types

#ifndef TYPES_H
#define TYPES_H

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
		int type;
		union {
			// number (64 bit)
			long long int num;
			// string
			char *str;
			// character
			char ch;
			// pointer
			void *ptr; // ids should point to symbol table
		};
	public:
		Obj(int);
		~Obj();
		char *toString();
	};

	// Abstract Syntax Tree
	class ObjTree {
		Obj *self;
		ObjTree *parent;
		ObjTree **children; // array
	public:
		ObjTree(Obj *, ObjTree *);
		~ObjTree();
	};

	// Object storage: name & ptr to Obj
	class ObjVar {
		char *name;
		Obj *obj;
	};

	char *TypeString(int typ);

}

#endif
