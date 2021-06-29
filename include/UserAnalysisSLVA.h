#ifndef USERANALYSISSLVA
#define USERANALYSISSLVA

#include "latest.h"
using namespace llvm;
using namespace std;

class UserAnalysisSLVA : public Analysis<NoAnalysisType,set<Value *>>
{
    protected:

    public:
  
    void printDataFlowValuesBackward(set<Value *> dfv)
    {
        cout << "{";
        for (auto i = dfv.begin(); i != dfv.end(); i++)
        {
            cout << (*i)->getName().str() << ", ";
        }
        cout << "}\n";
    }
    // Backward Component Starts : SLVA.
    set<Value *> computeInFromOut(Instruction &I)
    {
        set<Value *> total_liveness_info = OUT[&I].second;
        //PointsToMap SB = IN[&I].first;
        //set<void * > VB;
        /*
        for(auto it : SB)
        {
            VB.insert(it.first);
        }
        */
        if (isa<StoreInst>((I))) //check
        {
            if (total_liveness_info.find((I).getOperand(1)) != total_liveness_info.end() && !(isa<GlobalVariable>((I).getOperand(1)) && isa<GlobalVariable>((I).getOperand(0)))) //Comment out for LVA
            {
                total_liveness_info.insert((I).getOperand(0));
            }
            total_liveness_info.erase((I).getOperand(1));
        }
        else if (isa<ReturnInst>(I))
        {
            //errs()<<"Return Inst : "<<*I<<"\n";
            for (auto &op : ((I)).operands())
            {
                total_liveness_info.insert(op);
            }
        }
        else if (isa<LoadInst>((I)))
        {
            //errs()<<"Load Inst : "<<*I<<"\n";
            auto lhs = dyn_cast<Value>(&I);
            for (auto &op : ((I)).operands())
            {
                if (total_liveness_info.find(lhs) != total_liveness_info.end() && !isa<ConstantInt>(op) && !isa<ConstantFP>(op))
                {
                    total_liveness_info.insert(op);
                }
            }
            total_liveness_info.erase(lhs);
        }
        else if (!(isa<BranchInst>((I)) || isa<CallInst>((I)))) // For Arithmatic instructions and compare Instructions
        {
            // errs()<<"Not Branch and Call Inst : "<<*I<<"\n";
            auto lhs = dyn_cast<Value>(&I);
            for (auto &op : ((I)).operands())
            {
                if (total_liveness_info.find(lhs) != total_liveness_info.end() && !isa<ConstantInt>(op) && !isa<ConstantFP>(op))
                {
                    total_liveness_info.insert(op);
                }
            }
            total_liveness_info.erase(lhs);
        }
        else if (isa<BranchInst>((I)))
        {
            //errs()<<"Branch Inst : "<<*I<<"\n";
            int i = 0;
            for (auto &op : ((I)).operands())
                i++;
            if (i > 1)
            {
                total_liveness_info.insert((I).getOperand(0));
            }
        }
        else if (isa<CallInst>((I)))
        {
            //auto lhs = dyn_cast<Value>(&I);
            //total_liveness_info.erase(lhs);
            total_liveness_info = set<Value *>();
        } // Splitting global and locals.
        else
        {
            //errs()<<"Unknown Inst : "<<*I<<"\n";
            auto lhs = dyn_cast<Value>(&I);
            total_liveness_info.erase(lhs);
        }
        return total_liveness_info;
    }

    set<Value *> getBoundaryInformationBackward()
    {
        set<Value *> s;
        return s;
    }

    set<Value *> getInitialisationValueBackward()
    {
        set<Value *> s;
        return s;
    }

    set<Value *> performMeetBackward(set<Value *> s1, set<Value *> s2)
    {
        s1.insert(s2.begin(), s2.end());
        return s1;
    }

    bool EqualDataFlowValuesBackward(set<Value *> s1, set<Value *> s2)
    {
        if (s1 == s2)
            return true;
        return false;
    }

    set<Value *> getPurelyLocalComponentBackward(set<Value *> mp1)
    {
        set<Value *> temp1;
        for (auto i = mp1.begin(); i != mp1.end(); i++)
        {
            if (!isa<GlobalVariable>(*i))
            {
                temp1.insert(*i);
            }
        }
        return temp1;
    }

    set<Value *> getPurelyGlobalComponentBackward(set<Value *> mp1)
    {
        set<Value *> temp1;
        for (auto i = mp1.begin(); i != mp1.end(); i++)
        {
            if (isa<GlobalVariable>(*i))
            {
                temp1.insert(*i);
            }
        }
        return temp1;
    }

    set<Value *> getMixedComponentBackward(set<Value *> mp1)
    {
        set<Value *> temp1;
        return temp1;
    }

    set<Value *> getMergedValuesBackward(set<Value *> mp1, set<Value *> mp2)
    {
        //return mp1;
        //1--->global;
        //2--->local;
        //cout<<YELLOWB"Called";
        set<Value *> t1, t2;
        t1 = getPurelyGlobalComponentBackward(mp1);
        t2 = getPurelyLocalComponentBackward(mp2);
        t1.insert(t2.begin(), t2.end());
        return t1;
    }
  void printResults()
    {
        errs()<<BLUEB<<"\n--------------------------------------------------------"<<RST;
        errs()<<GREENB;
        auto context_label_counter=getContextLabelCounter();
        for(int i=0;i<=context_label_counter;i++)
        {
            errs()<<"\nLabel:"<<i<<" Function Name: "<<context_label_to_context_object_map[i].first->getName();
            set<Value *> fvalue=context_label_to_context_object_map[i].second.first.second;
             
            errs()<<YELLOWB<<"\n BACKWARD INFLOW VALUE: ";
            for(auto i : fvalue)
                {
                    errs()<<i->getName().str()<<", ";
                }
             errs()<<"\n"RST;

            set<Value *> outfvalue=context_label_to_context_object_map[i].second.second.second;
             
            errs()<<GREENB<<"\n BACKWARD OUTFLOW VALUE: ";
            for(auto i : outfvalue)
                {
                    errs()<<i->getName().str()<<", ";
                }
             errs()<<"\n"RST;


             //errs()<<" INFLOW VALUE: "<<context_label_to_context_object_map[i].second.first.second[0];
             //errs()<<" OUTFLOW VALUE: "<<context_label_to_context_object_map[i].second.second.second[0]; 
        }
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

