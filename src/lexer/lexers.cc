// Lexers.c
// contains all lexers

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

void *lava::lex_all(lava::Lexer *l) {
	if (!l->next()) {return NULL;}

	if (l->get() == '(') {
		l->push(new lava::Lexeme(TYPE_BP, l->emit()));
		return (void *) lex_list;
	} else if (l->get() == ')') {
		l->push(new lava::Lexeme(TYPE_EP, l->emit()));
		return (void *) lex_all;
	} else if (isspace(l->get())) {
		l->dump();
	} else {
		lava::Err((char *) "unknown symbol '%c' '%s'", l->get(), l->emit()->c_str());
	}

	return (void *) lex_all;
}

void *lava::lex_list(lava::Lexer *l) {
	if (!l->next()) {return NULL;}

	if (l->get() == ')') {
		l->backup();
		return (void *) lex_all;
	} else if (isalph(l->get())) {
		while (isalph(l->get())) {
			if (!l->next()) {
				lava::Err((char *) "unexpected eof");
				return NULL;
			}
		}

		l->backup();
		l->push(new lava::Lexeme(TYPE_ID, l->emit()));
		return (void *) lex_list;
	} else if (isnum(l->get())) {
		while (isnum(l->get())) {
			if (!l->next()) {
				lava::Err((char *) "unexpected eof");
				return NULL;
			}
		}

		l->backup();
		l->push(new lava::Lexeme(TYPE_N, l->emit()));
		return (void *) lex_list;
	} else if (isspace(l->get())) {
		l->dump();
	} else {
		lava::Err((char *) "unknown symbol '%c' '%s'", l->get(), l->emit()->c_str());
	}

	return (void *) lex_list;
}
