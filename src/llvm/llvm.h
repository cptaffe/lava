// Generates llvm ir

#ifndef LAVA_LLVM_LLVM_H_
#define LAVA_LLVM_LLVM_H_

// fuck ton of llvm includes
#include "llvm/IR/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "types/types.h"

namespace lava {

class llvm {
public:
  void gen(ObjTree &);
};

}

#endif // LAVA_LLVM_LLVM_H_
