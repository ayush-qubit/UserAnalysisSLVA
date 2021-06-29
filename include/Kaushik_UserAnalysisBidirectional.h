#ifndef USERANALYSISBIDIRECTIONAL
#define USERANALYSISBIDIRECTIONAL

#include "llvm/IR/Function.h"
#include "Analysis.h"
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
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "map"
#include "set"
#include "spatial/Benchmark/PTABenchmark.h"
#include "spatial/Graph/AliasGraph.h"
#include "spatial/Token/Alias.h"
#include "spatial/Token/AliasToken.h"
#include "spatial/Utils/CFGUtils.h"
#include "stack"
#include "queue"
using namespace llvm;
using namespace std;
using PointsToMap = spatial::AliasGraph<spatial::Alias>;
PointsToMap GlobalPointsToMap, InstIn;
std::map<Instruction *, PointsToMap> AliasIn, AliasOut;

class UserAnalysisBidirectional : public Analysis<PointsToMap, set<spatial ::Alias *>>
{
private:
    spatial::AliasTokens AT;
    spatial::AliasTokens A;

public:
    void printDataFlowValuesForward(PointsToMap dfv)
    {
        cout << MAGENTAB << dfv << RST;
    }

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
/*
set<spatial::Alias *> computeLivenessFromPTA(auto Var, set<spatial::Alias *> total_liveness_info,PointsToMap PTF)
    {
        
            for(auto it : PTF)
            {
                if(Var==it)
                {
                for(auto itr : it.second)
                {
                    if()

                }
                }
            }
    }
*/





    set<spatial::Alias *> computeInFromOut(Instruction &I)
    {
        Instruction *In = &I;
        set<spatial::Alias *> total_liveness_info = getBackwardComponentAtOutOfThisInstruction(I);
        PointsToMap PTF = getForwardComponentAtInOfThisInstruction(I);
        auto Aliases = AT.extractAliasToken((In));
        if (isa<StoreInst>((I))) //check
        {
            auto Aliases = AT.extractAliasToken((In));
            if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end() && !(Aliases[0]->isGlobalVar() && Aliases[1]->isGlobalVar())) //Comment out for LVA
            {
                //cout << CYANB << "Inserted " << Aliases[1]->getName().str() << RST << "\n";
                total_liveness_info.insert(Aliases[1]);
            }
                //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                    total_liveness_info.erase(Aliases[0]);
                }
           // total_liveness_info=computeLivenessFromPTA(Aliases[0],total_liveness_info, PTF);
        }
        else if (isa<ReturnInst>(I))
        {
            auto Aliases = AT.extractAliasToken((In));
            //errs()<<"Return Inst : "<<*I<<"\n";
            for (auto &op : Aliases)
            {
                ////// cout << CYANB << op->getName().str() << RST << "\n";
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
                    ////// cout << CYANB << op->getName().str() << RST << "\n";
                    total_liveness_info.insert(op);
                }
            }
            if (Aliases.size() >= 1)
                //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
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
                    ////// cout << CYANB << op->getName().str() << RST << "\n";
                    total_liveness_info.insert(op);
                }
            }
            if (Aliases.size() >= 1)
                //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                    total_liveness_info.erase(Aliases[0]);
                }
        }
        else if (isa<BranchInst>((I)) || isa<CmpInst>((I)))
        {
            //errs()<<"Branch Inst : "<<*I<<"\n";
            auto Aliases = AT.extractAliasToken((In));
            for (auto &op : Aliases)
            {
                ////// cout << CYANB << op->getName().str() << RST << "\n";

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
            if (Aliases.size() >= 1)
                //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";

                if (total_liveness_info.find(Aliases[0]) != total_liveness_info.end())
                {
                    //   cout << CYANB << "Deleted " << Aliases[0]->getName().str() << RST << "\n";
                    total_liveness_info.erase(Aliases[0]);
                }
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

    //Backward Component Ends : SLVA

    PointsToMap computeOutFromIn(Instruction &I)
    {
        A.getAliasToken("?", nullptr);
        InstIn = getForwardComponentAtInOfThisInstruction(I);
        auto InstInB = InstIn;
        Instruction *In = &I;
        Module *m = getCurrentModule();
        auto Aliases = AT.extractAliasToken((In));
        auto Redirections = AT.extractStatementType((In));
        set<spatial ::Alias *> SL = getBackwardComponentAtOutOfThisInstruction(I);
        set<spatial ::Alias *> SLB = getBackwardComponentAtInOfThisInstruction(I);

        if (Aliases.size() == 2)
        {
            // Default behavior is copy ie (1, 1)
            // for heap address in RHS make sure it is (x, 0)
            if (Aliases[1]->isMem())
                Redirections.second = 0;
            auto A2 = A.getAliasToken("?", nullptr);
            InstIn.insert(Aliases[0], A2, Redirections.first,
                          Redirections.second);
        }
        if (isa<StoreInst>(&I))
        {
            //errs() << "INST :";
            //errs() << YELLOWB << I << RST;
            auto Aliases = AT.extractAliasToken((In));
            auto Redirections = AT.extractStatementType((In));
            if (Aliases.size() == 2)
            {
                auto Pointee = InstIn.getPointee(Aliases[0]);
                if (Pointee.size() == 1)
                {
                    auto KillNode = *(Pointee.begin());
                    InstIn.erase(KillNode);
                }
                //cout << Aliases[0]->getName().str() << "\n";
                InstIn.insert(Aliases[0], Aliases[1], Redirections.first,
                              Redirections.second);
            }
        }
        if (isa<BranchInst>(&I) || isa<CmpInst>(&I))
        {
            return InstIn;
        }
        if (isa<LoadInst>(&I))
        {
            auto Aliases = AT.extractAliasToken((In));
            auto Redirections = AT.extractStatementType((In));
            if (Aliases.size() == 2)
            {
                if (Aliases[1]->isMem())
                {
                    Redirections.second = 0;
                }
                //cout << Aliases[0]->getName().str() << "\n";

                InstIn.insert(Aliases[0], Aliases[1], Redirections.first,
                              Redirections.second);

                //cout<<WHITEB<<"\nALIAS INFO inserted in InstIn: \n"<<Aliases[0]->getName().str()<<"->"<<Aliases[1]->getName().str()<<"\n"<<RST;
            }
        }

        PointsToMap temp2 = applyRelationRestriction(InstIn, SL);
        PointsToMap btemp2 = applyRelationRestriction(InstInB, SLB);

        printAtIn(btemp2, SLB);
        errs()<<YELLOWB<<I;
        printAtOut(temp2, SL);

        return InstIn;
    }

    void printAtIn(PointsToMap btemp2, set<spatial::Alias *> SLB)
    {
        cout << GREENB "\n----------------------------------------------------------------------------\n";
        cout << GREENB "\n--LIVENESS INFORMATION AT IN OF THIS PROGRAM POINT--\n";
        printDataFlowValuesBackward(SLB);

        cout << GREENB"\n--POINTS-TO INFORMATION  AT IN OF PROGRAM POINT AFTER RELATION RESTRICTION--\n";
        cout << btemp2;
        cout << GREENB "\n------------------------------XXXXXXX---------------------------------------\n"
             << RST;
    }

    void printAtOut(PointsToMap temp2, set<spatial::Alias *> SL)
    {
        cout << CYANB"\n--------------------------------------------------------------------------------\n";
        cout << CYANB "\n--LIVENESS INFORMATION AT OUT OF THIS PROGRAM POINT--\n";
        printDataFlowValuesBackward(SL);
        
        cout << CYANB"\n--POINTS-TO INFORMATION  AT OUT OF THIS PROGRAM POINT AFTER RELATION RESTRICTION--\n";
        cout << temp2;
        cout << CYANB"\n-------------------------------XXXXXX-------------------------------------------\n"
             << RST;
    }

    PointsToMap applyRelationRestriction(PointsToMap InstIn, set<spatial::Alias *> SL)
    {
        PointsToMap temp2;
        for (auto P : InstIn)
        {
            if (SL.find(P.first) != SL.end())
            {
                bool flag;
                //cout << YELLOWB << " " << P.first->getName().str() << RST << "  \n";
                for (auto it : P.second)
                {
                    auto rp = it;
                    flag = false;
                    if (P.first->isGlobalVar())
                    {
                        for (auto t2 : InstIn)
                        {
                            if (rp == t2.first && rp->isGlobalVar())
                            {
                                for (auto it : t2.second)
                                {
                                    flag = true;
                                    temp2.insert(rp, it);
                                }
                            }
                        }
                    }
                }
                for (auto X : P.second)
                {
                    if (!flag)
                        temp2.insert(P.first, X);
                }
                cout << RST;
            }
        }
        return temp2;
    }

    PointsToMap getBoundaryInformationForward() // main->first inst IN. GLobal Scope Data
    {
        PointsToMap mp;
        GlobalPointsToMap = mp;
        auto A2 = A.getAliasToken("?", nullptr);
        Module *M = getCurrentModule();
        for (auto &G : M->getGlobalList())
        {
            //if (G.getType()->getPointerElementType()->isPointerTy())
            auto Aliases = AT.extractAliasToken(&G);
            auto Redirections = AT.extractStatementType(&G);
            if (Aliases.size() == 2)
            {
                GlobalPointsToMap.insert(Aliases[0], Aliases[1],
                                         Redirections.first, Redirections.second);
                GlobalPointsToMap.insert(Aliases[1], A2,
                                         Redirections.first, Redirections.second);
                // Handle the case when a global variable is initialized with an
                // address
                if (llvm::GlobalVariable *Constant =
                        llvm::dyn_cast<GlobalVariable>(G.getInitializer()))
                {
                    GlobalPointsToMap.insert(Aliases[0],
                                             AT.getAliasToken(Constant), 2, 1);
                }
            }
        }
        PointsToMap temp1;
        for (auto P : GlobalPointsToMap)
        {
            for (auto X : P.second)
            {
                auto Pointee = GlobalPointsToMap.getPointee(P.first);
                if (Pointee.size() != 1)
                {
                    for (auto it : Pointee)
                    {
                        if (it != A2)
                        {
                            temp1.insert(P.first, it);
                        }
                    }
                }
                if (Pointee.size() == 1)
                {
                    temp1.insert(P.first, *(Pointee.begin()));
                }
            }
        }
        return temp1;
    }

    PointsToMap getInitialisationValueForward() // empty map for assumption.
    {
        PointsToMap mp1;
        return mp1;
    }

    PointsToMap performMeetForward(PointsToMap mp1, PointsToMap mp2) //union. //Need Instruction type here?
    {
        vector<PointsToMap> total_mp;
        total_mp.push_back(mp1);
        total_mp.push_back(mp2);
        PointsToMap total_res;
        total_res.merge(total_mp);
        return total_res;
    }

    bool EqualDataFlowValuesForward(PointsToMap mp1, PointsToMap mp2)
    {
        if (mp1 == mp2)
            return true;
        return false;
    }
    PointsToMap getPurelyLocalComponentForward(PointsToMap mp1)
    {
        PointsToMap temp1;
        for (auto P : mp1)
        {
            for (auto X : P.second)
            {
                auto Pointee = mp1.getPointee(P.first);
                for (auto it : Pointee)
                {
                    //std::cout<<"P.first : "<<P.first->getName().str()<<"\n";
                }
                //std::cout<<"P.second : "<<X->getName().str()<<"\n";
                if (!P.first->isGlobalVar() && !X->isGlobalVar())
                    temp1.insert(P.first, P.second);
            }
        }
        return temp1;
    }
    PointsToMap getPurelyGlobalComponentForward(PointsToMap mp1)
    {
        PointsToMap temp1;
        for (auto P : mp1)
        {
            for (auto X : P.second)
            {
                auto Pointee = mp1.getPointee(P.first);
                for (auto it : Pointee)
                {
                    //std::cout<<"P.first : "<<P.first->getName().str()<<"\n";
                }
                //std::cout<<"P.second : "<<X->getName().str()<<"\n";
                if (P.first->isGlobalVar() && X->isGlobalVar())
                    temp1.insert(P.first, P.second);
                //else ---> 1 global , 2 local --->(g,?)
            }
        }
        //cout<<WHITEB<<temp1<<RST;
        return temp1;
    }

    PointsToMap getMixedComponentForward(PointsToMap mp1)
    {
        //mp1-getPurelyGlobal(mp1)
        PointsToMap temp1;
        for (auto P : mp1)
        {
            for (auto X : P.second)
            {
                auto Pointee = mp1.getPointee(P.first);
                for (auto it : Pointee)
                {
                    //std::cout<<"P.first : "<<P.first->getName().str()<<"\n";
                }
                //std::cout<<"P.second : "<<X->getName().str()<<"\n";
                if (!P.first->isGlobalVar() || !X->isGlobalVar())
                    temp1.insert(P.first, P.second);
            }
        }
        return temp1;
    }

    PointsToMap getMergedValuesForward(PointsToMap mp1, PointsToMap mp2)
    {
        PointsToMap t1, t2;
        t1 = getPurelyGlobalComponentForward(mp1);
        t2 = getMixedComponentForward(mp2);
        //cout << t2;
        vector<PointsToMap> total_mp;
        total_mp.push_back(t1);
        total_mp.push_back(t2);
        PointsToMap total_res;
        total_res.merge(total_mp);
        return total_res;
    }

    PointsToMap getCombinedValuesAtCallForward(PointsToMap mp2, PointsToMap mp1)
    {
        PointsToMap t1, t2;
        t1 = getPurelyGlobalComponentForward(mp1);
        t2 = getMixedComponentForward(mp2);
        //cout << t2;
        vector<PointsToMap> total_mp;
        total_mp.push_back(t1);
        total_mp.push_back(t2);
        PointsToMap total_res;
        total_res.merge(total_mp);
        return total_res;
        //==========================================??
    }
    //Forward Component Ends : PA

    pair<PointsToMap, set<spatial ::Alias *>> CallInflowFunction(int context_label, Function *target_function, BasicBlock *bb, PointsToMap a1, set<spatial ::Alias *> d1)
    {
        //separating a1 into purely as a2;
        PointsToMap a2 = getPurelyGlobalComponentForward(a1);
        set<spatial ::Alias *> d2 = getPurelyGlobalComponentBackward(d1);
        return make_pair(a2, d2);
    }
    pair<PointsToMap, set<spatial ::Alias *>> CallOutflowFunction(int context_label, Function *target_function, BasicBlock *bb, PointsToMap a3, set<spatial ::Alias *> d3, PointsToMap a1, set<spatial ::Alias *> d1)
    {
        PointsToMap a4 = getPurelyGlobalComponentForward(a3);
        set<spatial ::Alias *> d4 = getPurelyGlobalComponentBackward(d3);
        PointsToMap a5 = getCombinedValuesAtCallForward(a1, a4);
        set<spatial ::Alias *> d5 = getCombinedValuesAtCallBackward(d4, d1);
        //a6=Apply relation-restriction on a5 using value d1 : d1 --> Liveness Information at OUT[callNode] and a5 is the computed Points-to information for call-node.
        //d6=Apply relation-restriction on d5 using value a1 : a1 --> Points-to Information at IN[callNode] and d5 is the computed liveness information for call-node.
        // return {a6,d6}.
        return make_pair(a5, d5);
    }

    void printInOutMaps()
    {
        int context_label_counter = getContextLabelCounter();
        for (int i = 0; i <= context_label_counter; i++)
        {
            errs() << MAGENTAB << "\nContext Label:" << i << " Function:" << getFunctionAssociatedWithThisContext(i)->getName() << RST;
            // errs()<<MAGENTAB<<"\nContext Label:"<<i<<" Function:"<<context_label_to_context_object_map[i].first->getName()<<RST;
            Function &function = *getFunctionAssociatedWithThisContext(i);
            for (BasicBlock &bb : function)
            {

                errs() << "\nBasicBlock: " CYANB " ";
                bb.printAsOperand(errs(), false);
                // if(CS_BB_IN.find(&bb)==CS_BB_IN.end()||CS_BB_OUT.find(&bb)==CS_BB_OUT.end())
                // {
                //     errs()<<"\n"REDB"No entry found!"<<RST;
                //     errs()<<"\n---------------------";
                //     continue;
                // }
                errs() << RST;
                errs() << GREENB << "\nIN(Forward): ";
                printDataFlowValuesForward(CS_BB_IN[make_pair(i, &bb)].first);
                errs() << RST;
                errs() << GREENB << "\nOUT(Forward):";
                printDataFlowValuesForward(CS_BB_OUT[make_pair(i, &bb)].first);
                errs() << RST;
                errs() << GREENB << "\nIN(Backward):";
                printDataFlowValuesBackward(CS_BB_IN[make_pair(i, &bb)].second);
                errs() << RST;
                errs() << GREENB << "\nOUT(Backward):";
                printDataFlowValuesBackward(CS_BB_OUT[make_pair(i, &bb)].second);
                errs() << RST;
                errs() << "\n---------------------";
                // errs()<<"\n"YELLOWB"Convergence:"<<convergence<<RST;
            }
        }
        errs() << "\n===============================================================";
    }
    void printResults()
    {
        /*
        int context_label_counter = getContextLabelCounter();
        errs() << BLUEB << "\n--------------------------------------------------------" << RST;
        errs() << GREENB;
        for (auto t : context_transition_graph)
        {
            errs() << GREENB "\n"
                   << t.first.first << " " << t.second << " BB:" << t.first.second->getParent()->getName() << " CallSite:" << *(t.first.second);
        }
        errs() << BLUEB << "\n--------------------------------------------------------" << RST;
        errs() << YELLOWB << "\n----------------------BIDIRECTIONAL----------------------------------" << RST;

        for (int i = 0; i <= context_label_counter; i++)
        {
            errs() << GREENB "\nLabel:" << i << " Function Name: " << getFunctionAssociatedWithThisContext(i)->getName();
            PointsToMap f_inflow_value = getForwardInflowForThisContext(i);
            PointsToMap f_outflow_value = getForwardOutflowForThisContext(i);
            auto b_inflow_value = getBackwardInflowForThisContext(i);
            auto b_outflow_value = getBackwardOutflowForThisContext(i);

            errs() << GREENB " INFLOW FORWARD: ";
            printDataFlowValuesForward(getForwardInflowForThisContext(i));
            errs() << GREENB " OUTFLOW FORWARD: ";
            printDataFlowValuesForward(getForwardOutflowForThisContext(i));

            errs() << GREENB " INFLOW BACKWARD: ";
            printDataFlowValuesBackward(getBackwardInflowForThisContext(i));
            errs() << GREENB " OUTFLOW BACKWARD: ";
            printDataFlowValuesBackward(getBackwardOutflowForThisContext(i));
        }

        errs() << RST;
        */
    }
};

#endif
