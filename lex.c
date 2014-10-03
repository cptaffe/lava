// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

typedef struct {
	char *buf;
	int typ;
} Lexeme;

typedef struct {
	char *buf;
	int pos;
	void *lexer; // current lexer
} Lexer;

typedef void *(* LexFunc) (Lexer *);

#include <unistd.h>

void *lexAll(Lexer *lex) {
	return NULL;
}

Lexeme *lex(Lexer *lex) {
	for (lex->lexer = lexAll; lex->lexer != NULL; lex->lexer = ((LexFunc) lex->lexer)(lex)){}
	return NULL;
}

int main() {
	Lexer lexer;
	lex(&lexer);
}