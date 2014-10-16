// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <iostream>
#include <vector>
#include "lex.h"

const size_t LEXBUF = 3;

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
int lava::Lexer::next() {
	if (len > front) {
		front++;
		return 1;
	} else {
		// allocate new string
		std::cout << "OUT OF READ SPACE" << std::endl;
		if (front - back > 0) {
			// copy memory
			std::string str = std::string((char *) &*buf->begin(), back, front-back);
			std::cout << str << std::endl;
		}
		back = front = 0;
		if (read(fd, (void *) &*buf->begin(), LEXBUF) > 0) {
			return 1;
		}
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
	return (&*buf->begin())[front - 1];
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
