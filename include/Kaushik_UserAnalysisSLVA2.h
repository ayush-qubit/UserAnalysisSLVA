#ifndef USERANALYSISSLVA
#define USERANALYSISSLVA

#include "llvm/IR/Function.h"
// #include "vector.h"
// #include "UserDataFlowValueForward.h"
// #include "UserDataFlowValueBackward.h"
#include "spatial/Benchmark/PTABenchmark.h"
#include "spatial/Graph/AliasGraph.h"
#include "spatial/Token/Alias.h"
#include "spatial/Token/AliasToken.h"
#include "spatial/Utils/CFGUtils.h"
#include "Analysis.h"
using namespace llvm;
using namespace std;

class UserAnalysisSLVA : public Analysis<NoAnalysisType, set<spatial::Alias *>>
{
protected:
    spatial::AliasTokens AT;
    spatial::AliasTokens A;

public:
    void printDataFlowValuesBackward(set<spatial::Alias *> dfv)
    {
        cout << GREENB;
        cout << "{";
        for (auto i = dfv.begin(); i != dfv.end(); i++)
        {
            cout << (*i)->getName().str() << ", ";
        }
        cout << "}\n";
        cout << RST;
    }

    //Backward Component Starts : SLVA

    set<spatial::Alias *> computeInFromOut(Instruction &I)
    {
        Instruction *In = &I;
        set<spatial::Alias *> total_liveness_info = getBackwardComponentAtOutOfThisInstruction(I);
        auto Aliases = AT.extractAliasToken((In));
        if (isa<StoreInst>((I))) //check
        {
            auto Aliases = AT.extractAliasToken((In));
            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end() && !(Aliases[0]->isGlobalVar() && Aliases[1]->isGlobalVar())) //Comment out for LVA
            {
                cout << CYANB << "Inserted " << Aliases[1]->getName().str() << RST << "\n";
                total_liveness_info.insert(Aliases[1]);
            }
            if(Aliases.size()>=1)
            cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
            {
                cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                total_liveness_info.erase(Aliases[0]);
            }
        }
        else if (isa<ReturnInst>(I))
        {
            auto Aliases = AT.extractAliasToken((In));
            //errs()<<"Return Inst : "<<*I<<"\n";
            for (auto &op : Aliases)
            {
                cout << CYANB << op->getName().str() << RST << "\n";
                total_liveness_info.insert(op);
            }
        }
        else if (isa<LoadInst>((I)))
        {
            //errs()<<"Load Inst : "<<*I<<"\n";
            auto Aliases = AT.extractAliasToken((In));
            for (auto &op : Aliases)
            {
                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    cout << CYANB << op->getName().str() << RST << "\n";
                    total_liveness_info.insert(op);
                }
            }
            if(Aliases.size()>=1)
            cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
            {
                cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                total_liveness_info.erase(Aliases[0]);
            }
        }
        else if (!(isa<BranchInst>((I)) || isa<CallInst>((I)))) // For Arithmatic instructions and compare Instructions
        {
            //errs()<<"Load Inst : "<<*I<<"\n";
            auto Aliases = AT.extractAliasToken((In));
            for (auto &op : Aliases)
            {
                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    cout << CYANB << op->getName().str() << RST << "\n";
                    total_liveness_info.insert(op);
                }
            }
            if(Aliases.size()>=1)
            cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
            {
                cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                total_liveness_info.erase(Aliases[0]);
            }
        }
        else if (isa<BranchInst>((I)) || isa<CmpInst>((I)))
        {
            //errs()<<"Branch Inst : "<<*I<<"\n";
            auto Aliases = AT.extractAliasToken((In));
            for (auto &op : Aliases)
            {
                cout << CYANB << op->getName().str() << RST << "\n";

                total_liveness_info.insert(op);
            }
        }
        else if (isa<CallInst>((I)))
        {
            //auto lhs = dyn_cast<Value>(&I);
            //total_liveness_info.erase(lhs);
            total_liveness_info = set<spatial::Alias *>();
        } // Splitting global and locals.
        else
        {
            auto Aliases = AT.extractAliasToken((In));
            //errs()<<"Unknown Inst : "<<*I<<"\n";
            if(Aliases.size()>=1)
            cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
            {
                cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                total_liveness_info.erase(Aliases[0]);
            }
        }
        errs() << GREENB << "\n"
               << I << RST;
        for (auto x : total_liveness_info)
        {
            errs() << WHITEB << "\n"
                   << x->getName().str() << RST;
        }

        return total_liveness_info;
    }

    set<spatial::Alias *> getBoundaryInformationBackward()
    {
        set<spatial::Alias *> s;
        return s;
    }

    set<spatial::Alias *> getInitialisationValueBackward()
    {
        set<spatial::Alias *> s;
        return s;
    }

    set<spatial::Alias *> performMeetBackward(set<spatial::Alias *> s1, set<spatial::Alias *> s2)
    {
        s1.insert(s2.begin(), s2.end());
        return s1;
    }

    bool EqualDataFlowValuesBackward(set<spatial::Alias *> s1, set<spatial::Alias *> s2)
    {
        if (s1 == s2)
            return true;
        return false;
    }

    set<spatial::Alias *> getPurelyLocalComponentBackward(set<spatial::Alias *> mp1)
    {
        set<spatial::Alias *> temp1;
        for (auto i = mp1.begin(); i != mp1.end(); i++)
        {
            if (!(*i)->isGlobalVar())
            {
                temp1.insert(*i);
            }
        }
        return temp1;
    }

    set<spatial::Alias *> getPurelyGlobalComponentBackward(set<spatial::Alias *> mp1)
    {
        set<spatial::Alias *> temp1;
        for (auto i = mp1.begin(); i != mp1.end(); i++)
        {
            if ((*i)->isGlobalVar())
            {
                temp1.insert(*i);
            }
        }
        return temp1;
    }

    set<spatial::Alias *> getMixedComponentBackward(set<spatial::Alias *> mp1)
    {
        set<spatial::Alias *> temp1;
        return temp1;
    }

    set<spatial::Alias *> getMergedValuesBackward(set<spatial::Alias *> mp1, set<spatial::Alias *> mp2)
    {
        //return mp1;
        //1--->global;
        //2--->local;
        //cout<<YELLOWB"Called";
        set<spatial::Alias *> t1, t2;
        t1 = getPurelyGlobalComponentBackward(mp1);
        t2 = getPurelyLocalComponentBackward(mp2);
        t1.insert(t2.begin(), t2.end());
        return t1;
    }

    set<spatial::Alias *> getCombinedValuesAtCallBackward(set<spatial::Alias *> mp1, set<spatial::Alias *> mp2)
    {
        set<spatial::Alias *> t1, t2;
        t1 = getPurelyGlobalComponentBackward(mp1);
        t2 = getPurelyLocalComponentBackward(mp2);
        t1.insert(t2.begin(), t2.end());
        return t1;
    }

    pair<NoAnalysisType, set<spatial::Alias *>> CallInflowFunction(int context_label, Function *target_function, BasicBlock *bb, NoAnalysisType a1, set<spatial::Alias *> d1)
    {
        //separating a1 into purely as a2;
        //NoAnalysisType a2=getPurelyGlobalComponentForward(a1);
        set<spatial::Alias *> d2 = getPurelyGlobalComponentBackward(d1);
        return make_pair(a1, d2);
    }
    pair<NoAnalysisType, set<spatial::Alias *>> CallOutflowFunction(int context_label, Function *target_function, BasicBlock *bb, NoAnalysisType a3, set<spatial::Alias *> d3, NoAnalysisType a1, set<spatial::Alias *> d1)
    {
        //NoAnalysisType a4=getPurelyGlobalComponentForward(a3);
        set<spatial::Alias *> d4 = getPurelyGlobalComponentBackward(d3);
        //NoAnalysisType a5= getCombinedValuesAtCallForward(a1,a4);
        // errs()<<WHITEB<<"\nOUTflow before combining local and global:";

        // for(auto x:d4)
        // {
        //     errs()<<"\t"<<x->getName();
        // }
        // // errs()<<"\nReturn this value";
        // errs()<<RST;

        set<spatial::Alias *> d5 = getCombinedValuesAtCallBackward(d4, d1);
        //a6=Apply relation-restriction on a5 using value d1 : d1 --> Liveness Information at OUT[callNode] and a5 is the computed Points-to information for call-node.
        //d6=Apply relation-restriction on d5 using value a1 : a1 --> Points-to Information at IN[callNode] and d5 is the computed liveness information for call-node.
        // return {a6,d6}.
        // errs()<<WHITEB<<"\nOUT after combining local and global:";

        // for(auto x:d5)
        // {
        //     errs()<<"\t"<<x->getName();
        // }
        // errs()<<"\nReturn this value";
        // errs()<<RST;
        return make_pair(a3, d5);
    }

    void printResults()
    {
        errs() << BLUEB << "\n--------------------------------------------------------" << RST;
        errs() << GREENB;
        auto context_label_counter = getContextLabelCounter();
        for (int i = 0; i <= context_label_counter; i++)
        {
            errs() << GREENB "\nLabel:" << i << " Function Name: " << getFunctionAssociatedWithThisContext(i)->getName();
            //NoAnalysisType f_inflow_value=getForwardInflowForThisContext(i);
            //NoAnalysisType f_outflow_value=getForwardOutflowForThisContext(i);
            set<spatial::Alias *> b_inflow_value = getBackwardInflowForThisContext(i);
            set<spatial::Alias *> b_outflow_value = getBackwardOutflowForThisContext(i);

            //errs()<<GREENB" INFLOW FORWARD: ";
            //printDataFlowValuesForward(getForwardInflowForThisContext(i));
            //errs()<<GREENB" OUTFLOW FORWARD: ";
            //printDataFlowValuesForward(getForwardOutflowForThisContext(i));

            errs() << GREENB " INFLOW BACKWARD: ";
            printDataFlowValuesBackward(getBackwardInflowForThisContext(i));
            errs() << GREENB " OUTFLOW BACKWARD: ";
            printDataFlowValuesBackward(getBackwardOutflowForThisContext(i));
        }

        //errs()<<" INFLOW VALUE: "<<context_label_to_context_object_map[i].second.first.second[0];
        //errs()<<" OUTFLOW VALUE: "<<context_label_to_context_object_map[i].second.second.second[0];
        //}
        //errs()<<BLUEB<<"\n--------------------------------------------------------"<<RST;
        //errs()<<BLUEB<<"\n--------------------------------------------------------"<<RST;
        //errs()<<GREENB;
        //for(auto t:context_transition_map)
        //{
        //errs()<<GREENB"\n"<<t.first.first<<" "<<t.second<<" CallSite:"<<*(t.first.second);
        //errs()<<" BB:";
        //(t.first.second->getParent())->printAsOperand(errs(),false);
        // b.printAsOperand(errs(),false);
        //errs()<<RST;
        // errs()<<GREENB"\n"<<t.first.first.first<<" "<<t.second<<" call number:"<<t.first.second;
        //}
        //errs()<<BLUEB<<"\n--------------------------------------------------------"<<RST;
    }
};

#endif
