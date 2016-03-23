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

    bool isPowerOf2(unsigned num) {
      while (num % 2 == 0 && num > 1) {
        num /= 2;
      }

      return num == 1;
    }

    bool runOnFunction(Function &function) override {
      errs() << function.getName() << "\n";

      for (auto &block : function) {
        for (auto &inst : block) {
          auto bitCastInst = dyn_cast<BitCastInst>(&inst);
          if (!bitCastInst) {
            continue;
          }
          errs() << "  found bitcast instruction\n";

          auto sourceVectorType =
              dyn_cast<VectorType>(bitCastInst->getOperand(0)->getType());
          if (!sourceVectorType) {
            continue;
          }
          auto elemSize = sourceVectorType->getScalarSizeInBits();
          auto numElems = sourceVectorType->getNumElements();
          errs() << "    from vector <" << numElems << " x i" << elemSize
                 << ">\n";

          if (!bitCastInst->getType()->isIntegerTy()) {
            continue;
          }
          auto width = bitCastInst->getType()->getPrimitiveSizeInBits();
          errs() << "    to integer i" << width << "\n";

          if (elemSize < 8 || !isPowerOf2(elemSize)) {
            errs() << "    i" << elemSize
                   << " is an invalid vector element type\n";
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
