// The "lava" headers are macro headers.
// lava.h contains all interpreter-wide information

#ifndef LAVA_LAVA_H_
#define LAVA_LAVA_H_

#include <string>
#include "types/types.h" // lava type system
#include "err/err.h" // lava erroring system
#include "lex.h" // lexer
#include "parse.h" // parser
#include "firstpass.h" // first pass optimizer

namespace lava {
  class Lava {
    Parser *parser;
    Lexer *lexer;
    FirstPass *firstpass;
  public:
    Lava(int);
    ~Lava();
    ObjTree *Eval(); // return evaluated tree for statement.
  };
}

#endif // LAVA_LAVA_H_
