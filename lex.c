// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <fcntl.h>
#include "lex.h"

const size_t LEXBUFF = 100;

lexeme *lex_que_pop(lexeme_que *que) {
	if (que->len == 0) {
		return NULL;
	} else {
		que->len--;
		return &que->que[que->len];
	}
}

void *lexAll(lexer *l) {
	write(1, &l->buf, l->len);
	return NULL;
}

// checks if lexeme is avaliable,
// else runs state machine.
lexeme *lex(lexer *l) {
	do {
		if (l->que->len > 0) {
			return lex_que_pop(l->que);
		}
	} while (l->lexer != NULL && (l->lexer = ((lex_func) l->lexer)(l)));
	return NULL;
}