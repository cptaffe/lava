
#ifndef LEXEME_H
#define LEXEME_H

#include <string>
#include "lava.h"

namespace lava {

	// lexeme returned to the caller
	class Lexeme {
	public:
		std::string buf;
		int typ;
		Lexeme(int typ, std::string buf);
		~Lexeme();
	};

}

#endif
