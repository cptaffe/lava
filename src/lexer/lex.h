// header for lexer

#ifndef LAVA_LEXER_LEX_H_
#define LAVA_LEXER_LEX_H_

#include <string>
#include <vector>
#include <list>
#include <queue>
#include "lexeme.h"
#include "que.h"

namespace lava { class Lexer; }

extern const size_t LEXBUFF;

// lexer struct
class lava::Lexer {
	int fd;
	std::vector<char> *buf;
	int len;
	int front;
	int back;
	void *lexer; // current lexer
public:
	lava::que<Lexeme *> *que;
	Lexer(int); // takes file descriptor
	~Lexer();
	Lexeme *lex();
	bool next();
	bool backup();
	char get();
	std::string *emit();
	void dump();
	void push(Lexeme *l);
};

// function pointer type
namespace lava {
typedef void *(*LexFunc)(Lexer *l);
void *lex_all(Lexer *l);
}

#endif // LAVA_LEXER_LEX_H_
