// header for lexer

#ifndef LEX_H
#define LEX_H

namespace lava { class Lexer; }

	extern const size_t LEXBUFF;

	#include <list>
	#include <queue>
	#include "lexeme.h"

	// lexer struct
	class lava::Lexer {
		int fd;
		char *buf;
		int len;
		int front;
		int back;
		void *lexer; // current lexer
		std::queue<Lexeme *> *que;
	public:
		Lexer(int); // takes file descriptor
		~Lexer();
		Lexeme *lex();
		void *lex_all(); // init value for Lexer.lexer
	private:
		int next();
		int backup();
		char get();
		char *emit();
		dump();
	};

	// function pointer type
	typedef void *(Lexer::*LexFunc)();

#endif
