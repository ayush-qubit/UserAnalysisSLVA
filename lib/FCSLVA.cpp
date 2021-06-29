#include "FCSLVA.h"
#include "Kaushik_UserAnalysisBidirectional.h"
//#include "Kaushik_UserAnalysisSLVA2.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"
#include "spatial/Benchmark/PTABenchmark.h"
#include "spatial/Graph/AliasGraph.h"
#include "spatial/Token/Alias.h"
#include "spatial/Token/AliasToken.h"
#include "spatial/Utils/CFGUtils.h"
#include "Analysis.h"
//#include "latest.h"
//#include "UserAnalysisSLVA.h"

using namespace llvm;
bool FCSLVAPass::runOnModule(Module& M) {
    UserAnalysisBidirectional backward_analysis_integer_object;
	errs()<<BLUEB"\n----------------------------------------------------------------\n";
	errs()<<REDB<<"\nBackward"RST;
    Module *m2= backward_analysis_integer_object.getCurrentModule();
    backward_analysis_integer_object.setCurrentModule(&(M));
	backward_analysis_integer_object.doAnalysis(M);	
    return false;
}

char FCSLVAPass::ID = 0;
static RegisterPass<FCSLVAPass> X(
    "aa-basic", "Basic implementation of strong liveness analysis in LLVM", true, true);
