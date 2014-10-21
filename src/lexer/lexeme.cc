// Lexeme functions

#include "lexeme.h"

namespace lava {

Lexeme::Lexeme(const int typ, std::string *buf) {
	this->typ = typ;
	this->buf = buf;
}

Lexeme::~Lexeme() {
	delete buf;
}

}
