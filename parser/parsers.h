
// parsers defined here.

#ifndef PARSERS_H
#define PARSERS_H

namespace lava {

  void *parse_all(Parser *p, Lexeme *l);
  void *parse_op(Parser *p, Lexeme *l);

}

#endif
