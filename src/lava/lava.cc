#include "lava.h"

#include <iostream>
#include <thread>

namespace lava {


  Lava::Lava(int fp) {
    lexer = new Lexer(fp);
    parser = new Parser(lexer->que);
    firstpass = new FirstPass();
    llvm = new lava::llvm();
  }

  Lava::~Lava() {
    delete lexer;
    delete parser;
    delete firstpass;
    delete llvm;
  }

  ObjTree *Lava::Eval() {

    // parallel execution
    std::thread lex_thread(&Lexer::lex, lexer);
    std::thread parse_thread(&Parser::parse, parser);
    std::thread eval_thread([](lava::que<ObjTree *> *objs, FirstPass *firstpass, lava::llvm *llvm){
        ObjTree *obj;
        objs->pop(obj);
        std::cout << "got one!" << std::endl;
        if (obj != NULL) {
          obj = firstpass->Pass(obj);
          std::cout << *obj << std::endl;
          llvm->gen(*obj);
        } else {
          return;
        }
    }, parser->objs, firstpass, llvm);

    lex_thread.join();
    std::cout << "done lexing" << std::endl;
    parse_thread.join();
    std::cout << "done parsing" << std::endl;
    eval_thread.join();
    std::cout << "done evaling" << std::endl;
    return NULL;
  }

}
