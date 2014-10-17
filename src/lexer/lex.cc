// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h> // memcpy
#include "lex.h"

const size_t LEXBUF = 10;

lava::Lexer::Lexer(const int fd) {
	front = back = 0;
	lexer = (void *) lex_all;
	buf = new std::vector<char>(LEXBUF);
	que = new std::queue<Lexeme *, std::list<Lexeme *> >;
	this->fd = fd;
	len = read(fd, (void *) &*buf->begin(), LEXBUF);
}

lava::Lexer::~Lexer() {
	delete que;
	// delete buf;
}

// Advance lexer one character
bool lava::Lexer::next() {
	if (len > front) {
		front++;
		return true;
	} else {
		int lexedlen = front - back;
		if (lexedlen > 0) {
			memcpy(&*buf->begin(), &*buf->begin() + back, lexedlen);
			back = 0; front = lexedlen;
		} else {
			back = 0; front = 1;
		}
		len = read(fd, (void *) (&*buf->begin() + lexedlen), LEXBUF);
		if (len > 0) {
			len += lexedlen;
			*((char *)  (&*buf->begin() + len)) = '\0';
			// std::cout << "str: '" << (char *) &*buf->begin() << "', len: " << len << std::endl;
			return true;
		} else {
			return false;
		}
	}
}

// Backup lexer one character
bool lava::Lexer::backup() {
	if (front > back) {
		front--;
		return true;
	} else {
		return false;
	}
}

// Get current character
char lava::Lexer::get() {
	return ((char *) &*buf->begin())[front - 1];
}

// Emit allocated string containing lexed characters
std::string *lava::Lexer::emit() {
	std::string *nbuf = new std::string((char *) &*buf->begin(), back, front - back);
	back = front;
	return nbuf;
}

// ignore currently lexed characters
void lava::Lexer::dump() {
	back = front;
}

// push to que
void lava::Lexer::push(Lexeme *l) {
	que->push(l);
}

// checks if lexeme is avaliable,
// else runs state machine.
lava::Lexeme *lava::Lexer::lex() {
	while (lexer != NULL || !que->empty()) {
		if (!que->empty()) {
			Lexeme *l = que->front();
			que->pop(); // removes value
			return l;
		} else {
			lexer = ((LexFunc) lexer)(this);
		}
	}

	return NULL;
}
