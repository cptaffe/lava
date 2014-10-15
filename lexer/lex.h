// header for lexer

#ifndef LEX_H
#define LEX_H

#include <string>
#include <queue>

namespace lava { class Lexer; }

extern const size_t LEXBUFF;

#include <list>
#include <queue>
#include "lexeme.h"

// lexer struct
class lava::Lexer {
public:
	int fd;
	std::string *buf;
	int len;
	int front;
	int back;
	void *lexer; // current lexer
	std::queue<Lexeme *, std::list<Lexeme *> > *que;
	Lexer(int); // takes file descriptor
	~Lexer();
	Lexeme *lex();
	int next();
	int backup();
	char get();
	std::string emit();
	void dump();
};

// function pointer type
namespace lava {
	typedef void *(*LexFunc)(Lexer *l);
	void *lex_all(Lexer *l);
}

#endif
