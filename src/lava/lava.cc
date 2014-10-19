#include "lava.h"

#include <iostream>

namespace lava {


  Lava::Lava(int fp) {
    lexer = new Lexer(fp);
    parser = new Parser();
    firstpass = new FirstPass();
  }

  Lava::~Lava() {
    delete lexer;
    delete parser;
    delete firstpass;
  }

  ObjTree *Lava::Eval() {
    Lexeme *lexeme;
    ObjTree *obj;
    while ((lexeme = lexer->lex()) != NULL) {
      obj = parser->parse(lexeme);
      if (obj != NULL) {
        obj = firstpass->Pass(obj);
        std::cout << *obj << std::endl;
      }
    }
    return obj;
  }

}
