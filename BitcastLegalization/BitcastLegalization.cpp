#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
using namespace llvm;

namespace {
  struct BitcastLegalization : public FunctionPass {
    static char ID;
    BitcastLegalization() : FunctionPass(ID) {}

    bool runOnFunction(Function &function) override {
      return false;
    }
  };
}

char BitcastLegalization::ID = 0;

static RegisterPass<BitcastLegalization> X(
  "bitcastlegalization", "Bitcast Legalization", false, false
);
