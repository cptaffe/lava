
#ifndef LEXEME_H
#define LEXEME_H

#include <string>
#include "lava.h"

namespace lava {

	// lexeme returned to the caller
	class Lexeme {
		std::string buf;
		int typ;
	public:
		Lexeme(int typ, std::string buf);
		~Lexeme();
	};

}

#endif
