
// parsers defined here.

#ifndef LAVA_PARSER_PARSERS_H_
#define LAVA_PARSER_PARSERS_H_

namespace lava {

void *parse_all(Parser *p, Lexeme *l);
void *parse_op(Parser *p, Lexeme *l);
void *parse_ops(Parser *p, Lexeme *l);

}

#endif // LAVA_PARSER_PARSERS_H_
