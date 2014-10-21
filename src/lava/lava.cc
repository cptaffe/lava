#include "lava.h"

#include <iostream>
#include <thread>

namespace lava {


  Lava::Lava(int fp) {
    lexer = new Lexer(fp);
    parser = new Parser(lexer->que);
    firstpass = new FirstPass();
  }

  Lava::~Lava() {
    delete lexer;
    delete parser;
    delete firstpass;
  }

  ObjTree *Lava::Eval() {

    // parallel execution
    std::thread lex_thread(&Lexer::lex, lexer);
    std::thread parse_thread(&Parser::parse, parser);
    std::thread eval_thread([](lava::que<ObjTree *> *objs, FirstPass *firstpass){
        while (true) {
            ObjTree *obj;
            objs->pop(obj);
            if (obj == NULL) {return;}
            // std::cout << "got one!" << std::endl;
            if (obj != NULL) {
              obj = firstpass->Pass(obj);
              std::cout << *obj << std::endl;
              delete obj;
            } else {
              return;
            }
        }
    }, parser->objs, firstpass);

    lex_thread.join();
    parse_thread.join();
    eval_thread.join();
    return NULL;
  }

}
