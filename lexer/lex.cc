// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // debug
#include <string>
#include <vector>
#include "lex.h"

const size_t LEXBUF = 100;

lava::Lexer::Lexer(int fd) {
	front = back = 0;
	lexer = (void *) lex_all;
	buf = new std::string(LEXBUF, 0);
	que = new std::queue<Lexeme *, std::list<Lexeme *> >;
	this->fd = fd;
	len = read(fd, (void *) buf->c_str(), LEXBUF);
}

lava::Lexer::~Lexer() {
	delete que;
	// delete buf;
}

// Advance lexer one character
int lava::Lexer::next() {
	if (len > front) {
		front++;
		return 1;
	} else {
		return 0;
	}
}

// Backup lexer one character
int lava::Lexer::backup() {
	if (front > back) {
		front--;
		return 1;
	} else {
		return 0;
	}
}

// Get current character
char lava::Lexer::get() {
	return buf->c_str()[front - 1];
}

// Emit allocated string containing lexed characters
std::string lava::Lexer::emit() {
	size_t size = front - back;
	std::string nbuf = std::string(buf[back], size);
	back = front;
	return nbuf;
}

// ignore currently lexed characters
void lava::Lexer::dump() {
	back = front;
}

// checks if lexeme is avaliable,
// else runs state machine.
lava::Lexeme *lava::Lexer::lex() {
	while (lexer != NULL || !que->empty()) {
		if (!que->empty()) {
			return que->front();
		} else {
			lexer = ((LexFunc) lexer)(this);
		}
	}

	return NULL;
}
