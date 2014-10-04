// header for lexer

#ifndef LEX_H
#define LEX_H

#include <unistd.h>
#include <fcntl.h>

extern const size_t LEXBUFF;

// lexeme returned to the caller
typedef struct {
	char *buf;
	int typ;
} lexeme;

// que of lexemes used by lexer
typedef struct {
	lexeme *que;
	int len;
} lexeme_que;

// lexer struct
typedef struct {
	int fd;
	char *buf;
	int len;
	int pos;
	void *lexer; // current lexer
	lexeme_que *que;
} lexer;

typedef void *(* lex_func) (lexer *);

// init value for lexer.lexer
void *lexAll(lexer *l);

// takes lexer, returns lexeme
lexeme *lex(lexer *l);

#endif