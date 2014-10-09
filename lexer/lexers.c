// Lexers.c
// contains all lexers

#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "lexers.h"
#include "../err/err.h"

lexeme *make_lexeme(int typ, char *buf) {
	lexeme *lex = malloc(sizeof(lexeme));
	lex->typ = typ;
	lex->buf = buf;
	return lex;
}

static int isnum(char c) {
	return c <= '9' && c >= '0';
}

static int isalph(char c) {
	return c <= 'z' && c >= 'a';
}

static int isspace(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

void *lex_all(lexer *l) {
	if (!lex_scan_next(l)){return NULL;}
	if (lex_scan_get(l) == '(') {
		lex_que_push(l->que, make_lexeme(TYPE_BP, lex_scan_emit(l)));
		return lex_list;
	} else if (lex_scan_get(l) == ')') {
		lex_que_push(l->que, make_lexeme(TYPE_EP, lex_scan_emit(l)));
		return lex_all;
	} else if (isspace(lex_scan_get(l))) {
		lex_scan_dump(l);
	} else {
		err("unknown symbol '%c' '%s'", lex_scan_get(l), lex_scan_emit(l));
	}
	return lex_all;
}

void *lex_list(lexer *l) {
	if (!lex_scan_next(l)){return NULL;}
	if (lex_scan_get(l) == ')') {
		lex_scan_backup(l);
		return lex_all;
	} else if (isalph(lex_scan_get(l))) {
		while (isalph(lex_scan_get(l))) {
			if (!lex_scan_next(l)){
				err("unexpected eof");
				return NULL;
			}
		}
		lex_scan_backup(l);
		lex_que_push(l->que, make_lexeme(TYPE_ID, lex_scan_emit(l)));
		return lex_list;
	} else if (isnum(lex_scan_get(l))) {
		while (isnum(lex_scan_get(l))) {
			if (!lex_scan_next(l)){
				err("unexpected eof");
				return NULL;
			}
		}
		lex_scan_backup(l);
		lex_que_push(l->que, make_lexeme(TYPE_N, lex_scan_emit(l)));
		return lex_list;
	} else if (isspace(lex_scan_get(l))) {
		lex_scan_dump(l);
	} else {
		err("unknown symbol '%c' '%s'", lex_scan_get(l), lex_scan_emit(l));
	}
	return lex_list;
}