// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <fcntl.h>
#include "lex.h"

const size_t LEXBUFF = 100;

lexeme *lex_que_pop(lexeme_que *que) {
	if (que->bottom == que->top) {
		return NULL;
	} else {
		return que->que[que->bottom++];
	}
}

void lex_que_push(lexeme_que *que, lexeme *lex) {
	if (que->top != 0 && que->top == que->bottom) {
		que->top = que->bottom = 0;
	}
	que->que[que->top++] = lex;
}

// List of lexers
#include "lexers.h"

// checks if lexeme is avaliable,
// else runs state machine.
lexeme *lex(lexer *l) {
	do {
		if (l->que->top > l->que->bottom) {
			return lex_que_pop(l->que);
		}
	} while (l->lexer != NULL && (l->lexer = ((lex_func) l->lexer)(l)));
	return NULL;
}