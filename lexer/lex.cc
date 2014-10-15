// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // debug
#include <string>
#include <vector>
#include "lex.h"


namespace lava {

	const size_t LEXBUF = 100;

	Lexer::Lexer(int fd) {
		top = bottom = 0;
		lexer = lex_all;
		buf = new std::string(LEXBUF, 0);
		que = new std::queue<Lexeme, std::list<Lexeme> >;
		fd = fd;
		len = read(fd, buf, LEXBUF);
	}

	void Lexer::~Lexer() {
		delete que;
		delete buf;
	}

	// Advance lexer one character
	int Lexer::next(lexer *l) {
		if (len > front) {
			front++;
			return 1;
		} else {
			return 0;
		}
	}

	// Backup lexer one character
	int Lexer::backup(lexer *l) {
		if (front > back) {
			front--;
			return 1;
		} else {
			return 0;
		}
	}

	// Get current character
	char Lexer::get(lexer *l) {
		return buf[front - 1];
	}

	// Emit allocated string containing lexed characters
	char *Lexer::emit(lexer *l) {
		int size = front - back;
		std::string nbuf = std::string(&buf[back], size);
		back = front;
		return nbuf;
	}

	// ignore currently lexed characters
	void Lexer::dump() {
		back = front;
	}

	// checks if lexeme is avaliable,
	// else runs state machine.
	Lexeme *Lexer::lex() {
		while (lexer != NULL || !que.empty()) {
			if (!que.empty()) {
				return que.pop();
			} else {
				lexer = ((LexFunc)x *this.*lexer)();
			}
		}

		return NULL;
	}

}
