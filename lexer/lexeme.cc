// Lexeme functions

#include "lexeme.h"
#include <stdlib.h>

namespace lava {

	Lexeme::Lexeme(int typ, std::string buf) {
		this->typ = typ;
		this->buf = buf;
	}

	Lexeme::~Lexeme() {
		//delete buf;
	}

}
