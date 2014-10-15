// Lexers.c
// contains all lexers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lava.h"
#include "lex.h"
#include "lexers.h"

static int isnum(char c) {
	return c <= '9' && c >= '0';
}

static int isalph(char c) {
	return c <= 'z' && c >= 'a';
}

static int isspace(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

void *lava::Lexer::lex_all() {
	if (!this.next()) {return NULL;}

	if (this.get() == '(') {
		this.que.push(new Lexeme(TYPE_BP, this.emit()));
		return lex_list;
	} else if (this.get() == ')') {
		this.que.push(new Lexeme(TYPE_EP, this.emit()));
		return lex_all;
	} else if (isspace(this.get())) {
		this.dump(l);
	} else {
		Err("unknown symbol '%c' '%s'", this.get(), this.emit());
	}

	return lex_all;
}

void *lava::Lexer::lex_list() {
	if (!this.next()) {return NULL;}

	if (this.get() == ')') {
		this.backup();
		return lex_all;
	} else if (isalph(this.get())) {
		while (isalph(this.get())) {
			if (!this.next()) {
				Err("unexpected eof");
				return NULL;
			}
		}

		this.backup();
		this.que.push(new Lexeme(TYPE_ID, this.emit(l)));
		return lex_list;
	} else if (isnum(this.get())) {
		while (isnum(this.get())) {
			if (!this.next()) {
				Err("unexpected eof");
				return NULL;
			}
		}

		this.backup();
		this.que.push(new Lexeme(TYPE_N, this.emit(l)));
		return lex_list;
	} else if (isspace(this.get(l))) {
		this.dump(l);
	} else {
		Err("unknown symbol '%c' '%s'", this.get(l), this.emit(l));
	}

	return lex_list;
}
