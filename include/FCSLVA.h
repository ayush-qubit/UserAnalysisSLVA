#ifndef FCSLVA_H
#define FCSLVA_H

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"

class FCSLVAPass : public llvm::ModulePass {
   public:
    static char ID;
    FCSLVAPass() : ModulePass(ID) {}
    bool runOnModule(llvm::Module& M) override;
};

#endif
