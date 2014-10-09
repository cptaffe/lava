// header for lexer

#ifndef LEX_H
#define LEX_H

extern const size_t LEXBUFF;

#include "lexeme.h"

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
	int front;
	int back;
	void *lexer; // current lexer
	lexeme_que *que;
} lexer;

typedef void *(* lex_func)(lexer *);

// init value for lexer.lexer
void *lex_all(lexer *l);

// lexeme que
lexeme *lex_que_get(lexeme_que *que);
void lex_que_push(lexeme_que *que, lexeme *lex);

// Lexical scanning
int lex_scan_next(lexer *l);
int lex_scan_backup(lexer *l);
char lex_scan_get(lexer *l);
char *lex_scan_emit(lexer *l);
void lex_scan_dump(lexer *l);

// takes lexer, returns lexeme
lexeme *lex(lexer *l);

#endif
