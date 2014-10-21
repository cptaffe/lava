// Lexers.c
// contains all lexers
#include "types/types.h"
#include "err/err.h"
#include "lex.h"
#include "lexers.h"

static bool isNum(const char c) {
	return c <= '9' && c >= '0';
}

static bool isAlph(const char c) {
	return c <= 'z' && c >= 'a';
}

static bool isSymb(const char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

static bool isSpace(const char c) {
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
	} else if (isSpace(l->get())) {
		l->dump();
	} else {
		err << "unknown symbol '" << l->get() << "' '" << l->emit()->c_str() << "'" << "\n";
	}

	return (void *) lex_all;
}

void *lava::lex_list(lava::Lexer *l) {
	if (!l->next()) {return NULL;}

	if (l->get() == ')' || l->get() == '(') {
		l->backup();
		return (void *) lex_all;
	} else if (isAlph(l->get()) || isSymb(l->get())) {
		while (isAlph(l->get()) || isSymb(l->get())) {
			if (!l->next()) {
				//lava::Err((char *) "unexpected eof");
				return NULL;
			}
		}

		l->backup();
		l->push(new lava::Lexeme(TYPE_ID, l->emit()));
		return (void *) lex_list;
	} else if (isNum(l->get())) {
		while (isNum(l->get())) {
			if (!l->next()) {
				lava::err << "unexpected eof" << "\n";
				return NULL;
			}
		}

		l->backup();
		l->push(new lava::Lexeme(TYPE_N, l->emit()));
		return (void *) lex_list;
	} else if (isSpace(l->get())) {
		l->dump();
	} else {
		lava::err << "unknown symbol" << "'" << l->get() << "' \"" << l->emit()->c_str() << "\n";
	}

	return (void *) lex_list;
}
