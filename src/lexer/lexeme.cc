// Lexeme functions

#include "lexeme.h"

namespace lava {

Lexeme::Lexeme(const int typ, const std::string *buf) {
	this->typ = typ;
	this->buf = new std::string(*buf);
}

Lexeme::~Lexeme() {
	delete buf;
}

}
