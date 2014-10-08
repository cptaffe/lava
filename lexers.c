// Lexers.c
// contains all lexers

#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "lexers.h"
#include "err.h"

lexeme *make_lexeme(int typ, char *buf) {
	lexeme *lex = malloc(sizeof(lexeme));
	lex->typ = typ;
	lex->buf = buf;
	return lex;
}

void *lex_all(lexer *l) {
	if (!lex_scan_next(l)){return NULL;}
	if (lex_scan_get(l) == '(') {
		lex_que_push(l->que, make_lexeme(LEXEME_BP, lex_scan_emit(l)));
		return lex_list;
	} else if (lex_scan_get(l) == ')') {
		lex_que_push(l->que, make_lexeme(LEXEME_EP, lex_scan_emit(l)));
		return lex_all;
	} else {
		char str[20];
		sprintf((char *) &str, "unknown symbol '%c' '%s'", lex_scan_get(l),lex_scan_emit(l));
		err(str);
	}
	return lex_all;
}

void *lex_list(lexer *l) {
	if (!lex_scan_next(l)){return NULL;}
	if (lex_scan_get(l) <= 'z' && lex_scan_get(l) >= 'a') {
		while (lex_scan_get(l) <= 'z' && lex_scan_get(l) >= 'a') {
			if (!lex_scan_next(l)){
				char str[20];
				sprintf((char *) &str, "unexpected eof");
				err(str);
				return NULL;
			}
		}
		lex_scan_backup(l);
		lex_que_push(l->que, make_lexeme(LEXEME_ID, lex_scan_emit(l)));
		return lex_list;
	} else if (lex_scan_get(l) <= '9' && lex_scan_get(l) >= '0') {
		while (lex_scan_get(l) <= '9' && lex_scan_get(l) >= '0') {
			if (!lex_scan_next(l)){
				char str[20];
				sprintf((char *) &str, "unexpected eof");
				err(str);
				return NULL;
			}
		}
		lex_scan_backup(l);
		lex_que_push(l->que, make_lexeme(LEXEME_N, lex_scan_emit(l)));
		return lex_list;
	} else {
		char str[20];
		sprintf((char *) &str, "unknown symbol '%c' '%s'", lex_scan_get(l),lex_scan_emit(l));
		err(str);
	}
	return lex_list;
}