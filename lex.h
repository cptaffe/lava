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
	lexeme **que;
	int top;
	int bottom;
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
void *lex_all(lexer *l);

// lexeme que
lexeme *lex_que_pop(lexeme_que *que);
void lex_que_push(lexeme_que *que, lexeme *lex);

// takes lexer, returns lexeme
lexeme *lex(lexer *l);

#endif