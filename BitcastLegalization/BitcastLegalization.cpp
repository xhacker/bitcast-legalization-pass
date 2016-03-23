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
      errs() << function.getName() << "\n";

      for (auto &block : function) {
        for (auto &inst : block) {
          auto bitCastInst = dyn_cast<BitCastInst>(&inst);
          if (bitCastInst) {
            errs() << "  found bitcast instruction\n";

            auto sourceVectorType = dyn_cast<VectorType>(bitCastInst->getOperand(0)->getType());
            if (sourceVectorType) {
              auto elemSize = sourceVectorType->getScalarSizeInBits();
              auto numElems = sourceVectorType->getNumElements();
              errs() << "    on vectors <" << numElems << " x i" << elemSize
                << ">\n";


            }
          }
        }
      }
      return false;
    }
  };
}

char BitcastLegalization::ID = 0;

static RegisterPass<BitcastLegalization> X(
  "bitcastlegalization", "Bitcast Legalization", false, false
);
