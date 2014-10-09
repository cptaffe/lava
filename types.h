// Defines types

#ifndef TYPES_H
#define TYPES_H

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
typedef struct {
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
} obj;

// Abstract Syntax Tree
struct obj_tree {
	struct obj *tree;
	struct obj_tree **child; // array
};
typedef struct obj_tree obj_tree;

// Object storage: name & ptr to Obj
typedef struct {
	char *name;
	obj *obj;
} obj_var;

#endif