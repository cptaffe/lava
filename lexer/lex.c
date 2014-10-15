// lex is a lexer for the lava interpreter
// lava is an interpreter for the basilisk language >= v.05

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h> // debug
#include "lex.h"

const size_t LEXBUFF = 100;

lexer *make_lexer(int fd) {
	lexer *l = calloc(sizeof(lexer), 1);
	l->lexer = lex_all;
	l->buf = calloc(sizeof(char), 100);
	l->que = malloc(sizeof(lexeme_que));
	l->que->que = calloc(sizeof(lexeme *), 10);
	l->fd = fd;
	l->len = read(l->fd, l->buf, LEXBUFF);
	return l;
}

void free_lexer(lexer *l) {
	free(l->que->que);
	free(l->que);
	free(l->buf);
	free(l);
}

// Get lexeme from que
lexeme *lex_que_get(lexeme_que *que) {
	if (que->bottom == que->top) {
		return NULL;
	} else {
		return que->que[que->bottom++];
	}
}

// Push lexeme to que
void lex_que_push(lexeme_que *que, lexeme *lex) {
	if (que->top != 0 && que->top == que->bottom) {
		que->top = que->bottom = 0;
	}

	que->que[que->top++] = lex;
}

// Advance lexer one character
int lex_scan_next(lexer *l) {
	if (l->len > l->front) {
		l->front++;
		return 1;
	} else {
		return 0;
	}
}

// Backup lexer one character
int lex_scan_backup(lexer *l) {
	if (l->front > l->back) {
		l->front--;
		return 1;
	} else {
		return 0;
	}
}

// Get current character
char lex_scan_get(lexer *l) {
	return l->buf[l->front - 1];
}

// Emit allocated string containing lexed characters
char *lex_scan_emit(lexer *l) {
	int size = l->front - l->back;
	char *nbuf = malloc(sizeof(char) * (size + 1));

	for (int i = 0; i < size; i++) {
		nbuf[i] = l->buf[i + l->back];
	}

	nbuf[size] = '\0';
	l->back = l->front;
	return nbuf;
}

// ignore currently lexed characters
void lex_scan_dump(lexer *l) {
	l->back = l->front;
}

// checks if lexeme is avaliable,
// else runs state machine.
lexeme *lex(lexer *l) {
	while (l->lexer != NULL || l->que->top > l->que->bottom) {
		if (l->que->top > l->que->bottom) {
			return lex_que_get(l->que);
		} else {
			l->lexer = ((lex_func) l->lexer)(l);
		}
	}

	return NULL;
}
