// Generates llvm ir

#ifndef LAVA_LLVM_LLVM_H_
#define LAVA_LLVM_LLVM_H_

// fuck ton of llvm includes
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/PassManager.h"
#include "llvm/CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

namespace lava {

class llvm {
public:
  void gen();
}

}

#endif LAVA_LLVM_LLVM_H_
