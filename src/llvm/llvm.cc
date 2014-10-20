
#include <iostream>
#include "llvm.h"
#include "keywords/keywords.h"
#include "err/err.h"

using namespace llvm;

// recursive code generation for select keywords

// TODO: note, this is super junky. The language can't
// assume that '+', '-', etc. are language reserved.

static Module *TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<std::string, Value*> NamedValues;

// generates IR for builtin
static Value *genBuiltin(lava::ObjTree &obj) {
  if (obj.self->str->compare(lava::KEYWORD_ADD) == 0) {
    std::cout << "add" << std::endl;
  }
  return NULL;
}

void lava::llvm::gen(ObjTree &obj) {
  if (obj.self == NULL) {
    for (std::vector<ObjTree *>::iterator it = obj.children->begin(); it != obj.children->end(); it++) {gen(**it);}
    return;
  }

  Obj &o = *obj.self;
  if (o.isId() && o.isBuiltin()) {
    genBuiltin(obj);
  }
  else {err << "(!) not a compilable fn: " << obj << "\n";}
}
