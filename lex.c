// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

typedef Lexeme *(*) (Lexer *) LexFunc;

typedef struct {
	char *buf;
	int pos;
	LexFunc lexer; // current lexer
} Lexer;

typedef struct {
	char *buf;
	int typ;
} Lexeme;

#include <unistd.h>

Lexeme *lex(Lexer *lex) {
	for (lex->lexer = lexAll; lex->lexer != NULL; lex->lexer = lex->lexer(lex)){}
}

Lexeme *lexAll(Lexer *lex) {
	return NULL;
}

int main() {
	Lexer lexer;
	lex(lexer);
}