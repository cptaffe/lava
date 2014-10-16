
#ifndef LAVA_LEXER_LEXEME_H_
#define LAVA_LEXER_LEXEME_H_

#include <string>
#include "lava.h"

namespace lava {

	// lexeme returned to the caller
	class Lexeme {
	public:
		std::string *buf;
		int typ;
		Lexeme(int typ, std::string *buf);
		~Lexeme();
	};

}

#endif // LAVA_LEXER_LEXEME_H_
