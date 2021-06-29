#ifndef ANALYSIS
#define ANALYSIS
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
// #include "llvm/ADT/DepthFirstIterator.h"
// #include "llvm/ADT/iterator_range.h"
#include "llvm/IR/CFG.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include<iostream>
#include<iomanip>
#include<queue>
#include<vector>
#include<stack>
#include<bits/stdc++.h>

#define RST "\033[0;m"
#define BLACKB "\033[1;90m"
#define REDB "\033[1;91m"
#define GREENB "\033[1;92m"
#define YELLOWB "\033[1;93m"
#define BLUEB "\033[1;94m"
#define MAGENTAB "\033[1;95m"
#define CYANB "\033[1;96m"
#define WHITEB "\033[1;97m"

#define BLACK "\u001b[;30m"
#define RED: "\u001b[;31m"
#define GREEN: "\u001b[;32m"
#define YELLOW: "\u001b[;33m"
#define BLUE: "\u001b[;34m"
#define MAGENTA: "\u001b[;35m"
#define CYAN: "\u001b[;36m"
#define WHITE: "\u001b[;37m"
using namespace llvm;
using namespace std;
enum NoAnalysisType {NoAnalyisInThisDirection};

template<class F,class B>
class Analysis
{
    private:
	F forward_component;
    B backward_component;
     Module *current_module;
    int context_label_counter;
    int current_analysis_direction;//0:initial pass 1:forward, 2:backward
	protected:
	std::map<Instruction*,std::pair<F,B>>IN,OUT;
    
    //debugging purpose
    std::map<BasicBlock*,std::pair<F,B>>BB_IN,BB_OUT;
    
    //List of contexts
    set<int>ProcedureContext;


    //mapping from context label to context object
    map<int,pair<Function*,pair<pair<F,B>,pair<F,B>>>>context_label_to_context_object_map;
    
    //mapping from context object to context label
    //mapping from function to  pair<inflow,outflow>
    //inflow and outflow are themselves pairs of forward and backward component values.
    //The forward and backward components are themselves pairs of G,L dataflow values.
    map<pair<Function*,pair<pair<F,B>,pair<F,B>>>,int>context_object_to_context_label_map;

    // mapping from (context label,basic block) to (forward and backward) data flow values
    map<pair<int,BasicBlock*>,std::pair<F,B>>CS_BB_IN,CS_BB_OUT;

    // worklist of (context label,basic block) for both directions of analysis
    stack<pair<int,BasicBlock*>>forward_worklist,backward_worklist;
    
    // mapping to check which entries are already part of the worklist
    map<pair<int,BasicBlock*>,bool>forward_worklist_contains_this_entry;
    map<pair<int,BasicBlock*>,bool>backward_worklist_contains_this_entry;
    
    // mapping from (context label,basic block) to target context label
    // map<pair<pair<int,BasicBlock*>,int>,int>transitions;
    
    // mapping from (context label,call site) to target context label
    map<pair<int,Instruction*>,int>context_transition_graph;//graph
	
    public:
	Analysis()
	{
        context_label_counter=-1;
	}
	int getContextLabelCounter()
    {
        return context_label_counter;
    }
    void setContextLabelCounter(int new_context_label_counter)
    {
        context_label_counter=new_context_label_counter;
    }
    int getCurrentAnalysisDirection()
    {
        return current_analysis_direction;
    }
    void setCurrentAnalysisDirection(int direction)
    {
        current_analysis_direction=direction;
    }

    
    void doAnalysis(Module &M);
    void INIT_CONTEXT(pair<Function*,pair<pair<F,B>,pair<F,B>>> context_object);
    void doAnalysisForward();
    void doAnalysisBackward();
    F NormalFlowFunctionForward(pair<int,BasicBlock*>);
    B NormalFlowFunctionBackward(pair<int,BasicBlock*>);
    int check_if_context_already_exists(pair<Function*,pair<pair<F,B>,pair<F,B>>> new_context_object);
    void drawSuperGraph(Module &M);
    void printWorklistMaps();
    void setCurrentModule(Module *);
    Module * getCurrentModule();
    virtual void printResults(){}
	
	

	virtual F computeOutFromIn(Instruction &I);
    virtual F getBoundaryInformationForward();//{}
    virtual F getInitialisationValueForward();//{}
    virtual F performMeetForward(F d1,F d2);//{}
    virtual bool EqualDataFlowValuesForward(F d1,F d2);//{}
    virtual F getPurelyLocalComponentForward(F dfv);
    virtual F getPurelyGlobalComponentForward(F dfv);
    virtual F getMixedComponentForward(F dfv);
    virtual F getMergedValuesForward(F dfv1,F dfv2);

    virtual void printDataFlowValuesForward(F dfv);

    virtual B computeInFromOut(Instruction &I);
    virtual B getBoundaryInformationBackward();//{}
    virtual B getInitialisationValueBackward();//{}
    virtual B performMeetBackward(B d1,B d2);//{}
    virtual bool EqualDataFlowValuesBackward(B d1,B d2);//{}
    virtual B getPurelyLocalComponentBackward(B dfv);
    virtual B getPurelyGlobalComponentBackward(B dfv);
    virtual B getMixedComponentBackward(B dfv);
    virtual B getMergedValuesBackward(B dfv1,B dfv2);
    
    virtual void printDataFlowValuesBackward(F dfv);
    
    void performSplittingBB(Function &f);
    void performFormalToActualMapping(Function &f);
    
    // void printInOutMapsBackward(Function &function);
    // void printInOutMapsForward(Function &function);

};

//========================================================================================
 template <class F,class B>
 void Analysis<F,B>::setCurrentModule(Module *module)
 {
     current_module=module;
 }

 template <class F,class B>
 Module* Analysis<F,B>::getCurrentModule()
 {
     return current_module;
 }

template <class F,class B>
void Analysis<F,B>::printDataFlowValuesForward(F dfv)
{
    errs()<<"\nThis function printDataFlowValuesForward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
void Analysis<F,B>::printDataFlowValuesBackward(F dfv)
{
    errs()<<"\nThis function printDataFlowValuesBackward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
B Analysis<F,B>::computeInFromOut(Instruction &I)
{
    errs()<<"\nThis function computeInFromOut() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
F Analysis<F,B>::computeOutFromIn(Instruction &I)
{
    errs()<<"\nThis function computeOutFromIn() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
F Analysis<F,B>::getBoundaryInformationForward(){
    errs()<<"\nThis function getBoundaryInformationForward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
B Analysis<F,B>::getBoundaryInformationBackward(){
    errs()<<"\nThis function getBoundaryInformationBackward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
F Analysis<F,B>::getInitialisationValueForward(){
    errs()<<"\nThis function getInitialisationValueForward() has not been implemented. EXITING !!\n";
    exit(-1);   
}

template <class F,class B>
B Analysis<F,B>::getInitialisationValueBackward(){
    errs()<<"\nThis function getInitialisationValueBackward() has not been implemented. EXITING !!\n";
    exit(-1);   
}

template <class F,class B>
F Analysis<F,B>::performMeetForward(F d1,F d2){
    errs()<<"\nThis function performMeetForward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
B Analysis<F,B>::performMeetBackward(B d1,B d2){
    errs()<<"\nThis function performMeetBackward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
bool Analysis<F,B>::EqualDataFlowValuesForward(F d1,F d2){
    errs()<<"\nThis function EqualDataFlowValuesForward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
bool Analysis<F,B>::EqualDataFlowValuesBackward(B d1,B d2){
    errs()<<"\nThis function EqualDataFlowValuesBackward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
B Analysis<F,B>::getPurelyLocalComponentBackward(B dfv)
{
    errs()<<"\nThis function getPurelyLocalComponentBackward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
F Analysis<F,B>::getPurelyLocalComponentForward(F dfv)
{
    errs()<<"\nThis function getPurelyLocalComponentForward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
B Analysis<F,B>::getPurelyGlobalComponentBackward(B dfv)
{
    errs()<<"\nThis function getPurelyGlobalComponentBackward() has not been implemented. EXITING !!\n";
    exit(-1);  
}

template <class F,class B>
F Analysis<F,B>::getPurelyGlobalComponentForward(F dfv)
{
    errs()<<"\nThis function getPurelyGlobalComponentForward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
B Analysis<F,B>::getMixedComponentBackward(B dfv)
{
    errs()<<"\nThis function getMixedComponentBackward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
F Analysis<F,B>::getMixedComponentForward(F dfv)
{
    errs()<<"\nThis function getMixedComponentForward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
B Analysis<F,B>::getMergedValuesBackward(B dfv1,B dfv2)
{
    errs()<<"\nThis function getMergedValuesBackward() has not been implemented. EXITING !!\n";
    exit(-1);
}

template <class F,class B>
F Analysis<F,B>::getMergedValuesForward(F dfv1,F dfv2)
{
    errs()<<"\nThis function getMergedValuesForward() has not been implemented. EXITING !!\n";
    exit(-1);
}
//========================================================================================

template <class F,class B>
void Analysis<F,B>::doAnalysis(Module &M)
{
    
    // for(auto &ginst:M.getGlobalList())
    // {
    //     // Instruction I=*ginst;
    //     errs()<<YELLOWB<<ginst<<RST;
    //     errs()<<"\n";
    //     GlobalVariable &gv=ginst;
    //     for(auto user_of_gv : gv.users())
    //     {
    //         if(Instruction *I = llvm::dyn_cast<llvm::Instruction>(user_of_gv))
    //         {
    //             errs()<<GREENB<<*I<<RST;
    //             errs()<<"\n";
    //         }
    //     }
    // }
    // return ;
    //======================================================================================
    setCurrentModule(&M);
    /*
    for(Function &function: M)
	{
		errs()<<BLUEB"\n----------------------------------------------------------------\n";
		errs()<<REDB<<function.getName()<<RST;
		if(function.size()>0)
			performFormalToActualMapping(function);
		errs()<<BLUEB"\n----------------------------------------------------------------\n";
	}
    */
    
	errs()<<RST;
    //return;
    //======================================================================================

    //======================================================================================
    for(Function &function: M)
	{
		errs()<<BLUEB"\n----------------------------------------------------------------\n";
		errs()<<REDB<<function.getName()<<RST;
		if(function.size()>0)
			performSplittingBB(function);
		errs()<<BLUEB"\n----------------------------------------------------------------\n";
	}
    
	errs()<<RST;
    //======================================================================================

    int i=0;
    for(Function &function: M)
	{
		errs() <<"\nMy code: Function Fetched: "<<++i<<". "<< function.getName();
		if(function.getName()=="main")
		{
			errs()<<"\n"REDB"Main Found!"RST;
            F forward_inflow_bi;//=getBoundaryInformationForward();
            B backward_inflow_bi;//=getBoundaryInformationBackward();
            F forward_outflow_bi;
            B backward_outflow_bi;
            Function *fptr=&function;
            if(std::is_same<F, NoAnalysisType>::value)
            {
                // forward_bi=NoAnalyisInThisDirection;   
            }
            else
            {
                forward_inflow_bi=getBoundaryInformationForward();
            }
            if(std::is_same<B, NoAnalysisType>::value)
            {
                // forward_bi=NoAnalyisInThisDirection;   
            }
            else
            {
                backward_inflow_bi=getBoundaryInformationBackward();
            }
            INIT_CONTEXT(make_pair(fptr,make_pair(make_pair(forward_inflow_bi,backward_inflow_bi),make_pair(forward_outflow_bi,backward_outflow_bi))));
            errs()<<REDB"\nSize of Worklist:"<<forward_worklist.size()<<" and "<<backward_worklist.size()<<RST;
		}
    }
    errs()<<REDB<<"\nFWS:"<<forward_worklist.size()<<" BWS:"<<backward_worklist.size()<<RST;
    errs()<<"\n------------------------BEGIN ANALYSIS----------------------------------";
    if(std::is_same<F, NoAnalysisType>::value)
    {
        //backward analysis
        int backward_iteration_count=0;
        while (backward_worklist.size()>0)
        {
            doAnalysisBackward();
            backward_iteration_count++;
        }
        errs()<<REDB<<"\nbackward_iteration_count:"<<backward_iteration_count;
    }
    else if(std::is_same<B, NoAnalysisType>::value)
    {
        //forward analysis
        int forward_iteration_count=0;
        while (forward_worklist.size()>0)
        {
            doAnalysisForward();
            forward_iteration_count++;
        }
        errs()<<MAGENTAB"\nforward_iteration_count:"<<forward_iteration_count<<" FW size:"<<forward_worklist.size()<<RST;
    }
    else
    {
        int fi=1,bi=1;
        while (forward_worklist.size()>0||backward_worklist.size()>0)
        { 
            errs()<<MAGENTAB<<"\nBackward Iteration:"<<bi++<<RST;
            current_analysis_direction=2;
            while(backward_worklist.size()>0)
            {
                doAnalysisBackward();
            }
            errs()<<MAGENTAB<<"\nForward Iteration:"<<fi++<<RST;
            current_analysis_direction=1;
            while(forward_worklist.size()>0)
            {
                doAnalysisForward();
            }
            break;
        }
    }
    errs()<<REDB"\nTotal Contexts created:"<<ProcedureContext.size()<<" Context Counter"<<context_label_counter<<RST;
    printResults();
}

template <class F,class B>
void Analysis<F,B>::INIT_CONTEXT(pair<Function*,pair<pair<F,B>,pair<F,B>>> context_object)//,F forward_component,B backward_component)
{
    Function &function=*(context_object.first);
    errs()<<REDB<<"\nInit Context called! for function: "<<function.getName()<<RST;
    context_label_counter++;
    int current_context_label=context_label_counter;

    if(std::is_same<F, NoAnalysisType>::value)
    {
        //backward analysis
        // map<int,pair<Function*,pair<pair<F,B>,pair<F,B>>>>context_label_to_context_object_map;
        context_label_to_context_object_map[current_context_label].first=&function;
        // errs()<<MAGENTAB<<"\nSetting Inflow Backward:"<<context_object.second.first.second[0]<<" for label:"<<current_context_label;
        // context_label_to_context_object_map[current_context_label].second.first.second=context_object.second.first.second;//setting inflow backward
        context_label_to_context_object_map[current_context_label].second.second.second=getInitialisationValueBackward();//setting outflow backward
        context_object_to_context_label_map[context_label_to_context_object_map[current_context_label]]=current_context_label;
        ProcedureContext.insert(current_context_label);

        for(BasicBlock *BB:inverse_post_order(&function.back()))
        {
            BasicBlock &b=*BB;
            errs()<<"\nBasicBlock: ";
            b.printAsOperand(errs(),false);
            forward_worklist.push(make_pair(current_context_label,&b));
            backward_worklist.push(make_pair(current_context_label,&b));
            forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
            backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
            // CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
            CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
            // CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
            CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
            
            //initialise IN-OUT maps for every instruction
            for(auto inst=b.begin();inst!=b.end();inst++)
            {
                errs()<<"\n"<<*inst;
                IN[&(*inst)].second=getInitialisationValueBackward();
                OUT[&(*inst)].second=getInitialisationValueBackward();
            }
        }
        if(current_context_label==0)//main function with first invocation
        {
            context_label_to_context_object_map[current_context_label].second.first.second=getBoundaryInformationBackward();//setting inflow backward
        }
        else
        {
            context_label_to_context_object_map[current_context_label].second.first.second=context_object.second.first.second;//setting inflow backward
        }
        // errs()<<MAGENTAB<<"\nSetting CS BB OUT Backward:"<<context_object.second.first.second[0]<<" for label:"<<current_context_label;
        CS_BB_OUT[make_pair(current_context_label,&function.back())].second=context_label_to_context_object_map[current_context_label].second.first.second;

    }
    else if(std::is_same<B, NoAnalysisType>::value)
    {
        //forward analysis
        context_label_to_context_object_map[current_context_label].first=&function;
        // context_label_to_context_object_map[current_context_label].second.first.first=context_object.second.first.first;//setting inflow forward
        context_label_to_context_object_map[current_context_label].second.second.first=getInitialisationValueForward();//setting outflow forward
        context_object_to_context_label_map[context_label_to_context_object_map[current_context_label]]=current_context_label;
        ProcedureContext.insert(current_context_label);
        
        errs()<<CYANB"\nNumber of Basic Blocks:"<<function.size()<<RST;
        for(BasicBlock *BB:post_order(&function.getEntryBlock()))
        {
            BasicBlock &b=*BB;
            errs()<<"\nBasicBlock: ";
            b.printAsOperand(errs(),false);
            forward_worklist.push(make_pair(current_context_label,&b));
            backward_worklist.push(make_pair(current_context_label,&b));
            forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
            backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
            CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
            // CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
            CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
            // CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
            
            //initialise IN-OUT maps for every instruction
            for(auto inst=b.begin();inst!=b.end();inst++)
            {
                errs()<<"\n"<<*inst;
                IN[&(*inst)].first=getInitialisationValueForward();
                OUT[&(*inst)].first=getInitialisationValueForward();
            }
        }
        if(current_context_label==0)//main function with first invocation
        {
            context_label_to_context_object_map[current_context_label].second.first.first=getBoundaryInformationForward();//setting inflow forward
        }
        else
        {
            context_label_to_context_object_map[current_context_label].second.first.first=context_object.second.first.first;//setting inflow forward
        }
        CS_BB_IN[make_pair(current_context_label,&function.getEntryBlock())].first=context_label_to_context_object_map[current_context_label].second.first.first;
    }
    else
    {
        //bidirectional analysis
        context_label_to_context_object_map[current_context_label].first=&function;

        if(current_analysis_direction==1)
        {
            errs()<<CYANB<<"\nforward init-context"<<RST;
            context_label_to_context_object_map[current_context_label].second.second.first=getInitialisationValueForward();//setting outflow forward
            // context_label_to_context_object_map[current_context_label].second.first.first=context_object.second.first.first;//setting inflow forward
            context_object_to_context_label_map[context_label_to_context_object_map[current_context_label]]=current_context_label;
            ProcedureContext.insert(current_context_label);
            for(BasicBlock *BB:post_order(&function.getEntryBlock()))
            {
                BasicBlock &b=*BB;
                // errs()<<"\nBasicBlock: ";
                // b.printAsOperand(errs(),false);
                forward_worklist.push(make_pair(current_context_label,&b));
                // backward_worklist.push(make_pair(current_context_label,&b));
                forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                // backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                // CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                // CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                
                //initialise IN-OUT maps for every instruction
                for(auto inst=b.begin();inst!=b.end();inst++)
                {
                    // errs()<<"\n"<<*inst;
                    IN[&(*inst)].first=getInitialisationValueForward();
                    OUT[&(*inst)].first=getInitialisationValueForward();
                    // IN[&(*inst)].second=getInitialisationValueBackward();
                    // OUT[&(*inst)].second=getInitialisationValueBackward();
                }
            }
        }
        else if(current_analysis_direction==2)
        {
            errs()<<CYANB<<"\nbackward init-context"<<RST;
            context_label_to_context_object_map[current_context_label].second.second.second=getInitialisationValueBackward();//setting outflow backward    
            // context_label_to_context_object_map[current_context_label].second.first.second=context_object.second.first.second;//setting inflow backward
            context_object_to_context_label_map[context_label_to_context_object_map[current_context_label]]=current_context_label;
            ProcedureContext.insert(current_context_label);
            for(BasicBlock *BB:inverse_post_order(&function.back()))
            {
                BasicBlock &b=*BB;
                // errs()<<"\nBasicBlock: ";
                // b.printAsOperand(errs(),false);
                // forward_worklist.push(make_pair(current_context_label,&b));
                backward_worklist.push(make_pair(current_context_label,&b));
                // forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                // CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                // CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                
                //initialise IN-OUT maps for every instruction
                for(auto inst=b.begin();inst!=b.end();inst++)
                {
                    // errs()<<"\n"<<*inst;
                    // IN[&(*inst)].first=getInitialisationValueForward();
                    // OUT[&(*inst)].first=getInitialisationValueForward();
                    IN[&(*inst)].second=getInitialisationValueBackward();
                    OUT[&(*inst)].second=getInitialisationValueBackward();
                }
            }
            
        }
        else
        {
        
            context_label_to_context_object_map[current_context_label].second.second.second=getInitialisationValueBackward();//setting outflow backward
            context_label_to_context_object_map[current_context_label].second.second.first=getInitialisationValueForward();//setting outflow forward
            
            // context_label_to_context_object_map[current_context_label].second.first.second=context_object.second.first.second;//setting inflow backward
            // context_label_to_context_object_map[current_context_label].second.first.first=context_object.second.first.first;//setting inflow forward
            
            
            context_object_to_context_label_map[context_label_to_context_object_map[current_context_label]]=current_context_label;
            ProcedureContext.insert(current_context_label);
            for(BasicBlock *BB:inverse_post_order(&function.back()))
            {
                //populate backward worklist
                BasicBlock &b=*BB;
                // errs()<<"\nBasicBlock: ";
                // b.printAsOperand(errs(),false);
                // forward_worklist.push(make_pair(current_context_label,&b));
                backward_worklist.push(make_pair(current_context_label,&b));
                // forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                // CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                // CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                
                //initialise IN-OUT maps for every instruction
                for(auto inst=b.begin();inst!=b.end();inst++)
                {
                    // errs()<<"\n"<<*inst;
                    // IN[&(*inst)].first=getInitialisationValueForward();
                    // OUT[&(*inst)].first=getInitialisationValueForward();
                    IN[&(*inst)].second=getInitialisationValueBackward();
                    OUT[&(*inst)].second=getInitialisationValueBackward();
                }
            }
            for(BasicBlock *BB:post_order(&function.getEntryBlock()))
            {
                //populate forward worklist
                BasicBlock &b=*BB;
                // errs()<<"\nBasicBlock: ";
                // b.printAsOperand(errs(),false);
                forward_worklist.push(make_pair(current_context_label,&b));
                // backward_worklist.push(make_pair(current_context_label,&b));
                forward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                // backward_worklist_contains_this_entry[make_pair(current_context_label,&b)]=true;
                CS_BB_IN[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                // CS_BB_IN[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                CS_BB_OUT[make_pair(current_context_label,&b)].first=getInitialisationValueForward();
                // CS_BB_OUT[make_pair(current_context_label,&b)].second=getInitialisationValueBackward();
                
                //initialise IN-OUT maps for every instruction
                for(auto inst=b.begin();inst!=b.end();inst++)
                {
                    // errs()<<"\n"<<*inst;
                    IN[&(*inst)].first=getInitialisationValueForward();
                    OUT[&(*inst)].first=getInitialisationValueForward();
                    // IN[&(*inst)].second=getInitialisationValueBackward();
                    // OUT[&(*inst)].second=getInitialisationValueBackward();
                }
            }
        }
        //irresepective of the current direction of analysis, the INFLOW values need to be set.
        if(current_context_label==0)//main function with first invocation
        {
            context_label_to_context_object_map[current_context_label].second.first.second=getBoundaryInformationBackward();//setting inflow backward
            context_label_to_context_object_map[current_context_label].second.first.first=getBoundaryInformationForward();//setting inflow forward
        }
        else
        {
            context_label_to_context_object_map[current_context_label].second.first.second=context_object.second.first.second;//setting inflow backward
            context_label_to_context_object_map[current_context_label].second.first.first=context_object.second.first.first;//setting inflow forward
        }
        CS_BB_IN[make_pair(current_context_label,&function.getEntryBlock())].first=context_label_to_context_object_map[current_context_label].second.first.first;
        CS_BB_OUT[make_pair(current_context_label,&function.back())].second=context_label_to_context_object_map[current_context_label].second.first.second;
    
    }
    errs()<<REDB<<"\nInit Context ENDED! for function: "<<function.getName()<<RST;
}

template <class F,class B>
void Analysis<F,B>::doAnalysisForward()
{
    while(!forward_worklist.empty())//step 2
    {
        //step 3 and 4
        pair<int,BasicBlock*> current_pair=forward_worklist.top();
        int current_context_label;
        BasicBlock *bb;
        current_context_label=forward_worklist.top().first;
        bb=forward_worklist.top().second;
        forward_worklist.pop();
        forward_worklist_contains_this_entry[make_pair(current_context_label,bb)]=false;

        BasicBlock &b=*bb;
        Function *f=context_label_to_context_object_map[current_context_label].first;
        Function &function=*f;
        errs()<<BLUEB"\nContext Label: "<<current_context_label<<" BasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<" Function Name: "<<f->getName()<<" WS:"<<forward_worklist.size()<<RST;
        
        //step 5
        if(bb!=(&function.getEntryBlock()))
        {
            errs()<<"\nNon-Entry Block";
            //step 6
            CS_BB_IN[current_pair].first=getInitialisationValueForward();
            
            //step 7 and 8
            for(auto pred_bb:predecessors(bb))
            {
                errs()<<"\nPred BB: ";
                pred_bb->printAsOperand(errs(),false);
                errs() << "\t"; //Label of Basic block
                CS_BB_IN[current_pair].first=performMeetForward(CS_BB_IN[current_pair].first,CS_BB_OUT[make_pair(current_pair.first,pred_bb)].first);                
            }
        }
        else
        {
            errs()<<"\nEntry Block";
            //In value of this node is same as INFLOW value
            // errs()<<context_label_to_context_object_map[current_context_label].second.first.first[0]; //won't work
            CS_BB_IN[current_pair].first=context_label_to_context_object_map[current_context_label].second.first.first;
            //Local component: CS_BB_IN[current_pair].first.second = getBIForward()
        }
        
        //step 9
        F previous_value_at_out_of_this_node=CS_BB_OUT[current_pair].first;
        
        //step 10
        bool contains_a_method_call=false;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            Instruction &I=*inst;
            if ( CallInst *fnn = dyn_cast<CallInst>(&I))
            {
                contains_a_method_call=true;
                errs()<<YELLOWB"\n----------------------------------------------"RST;
                errs()<<REDB"\nMethod Call found in basic block: "<<inst->getParent()->getName()<<RST;
                
                break;
            }
        }
        // errs()<<MAGENTAB"\nContains a method call: "<<contains_a_method_call<<RST;
        if(contains_a_method_call)
        {
            F prev=CS_BB_IN[current_pair].first;
            int call_number=0;
            
            //step 11
            for(auto inst=b.begin();inst!=b.end();inst++)
            {
                Instruction &I=*inst;
                if ( CallInst *ci = dyn_cast<CallInst>(&I))
                {

                    Function* target_function= ci->getCalledFunction();
                    // errs()<<REDB"\nCalled Function: "<<target_function->getName()<<RST;
                    if((*target_function).size()==0)
                    {
                        continue;//this is an inbuilt function so doesnt need to be processed.
                    }
                    call_number++;
                    errs()<<"\n"<<*inst;
                    
                    /*
                    At the call instruction, the value at IN should be splitted into two components:
                    1) Purely Global and 2) Mixed.
                    The purely global component is given to the start of callee.
                    */
                    
                    //step 12
                    F new_inflow_forward=getPurelyGlobalComponentForward(prev);
                    B new_inflow_backward;
                    F new_outflow_forward;
                    B new_outflow_backward;
                    
                    //step 13
                    pair<Function*,pair<pair<F,B>,pair<F,B>>> new_context_object=make_pair(target_function,make_pair(make_pair(new_inflow_forward,new_inflow_backward),make_pair(new_outflow_forward,new_outflow_backward)));

                    //===========================================================
                    IN[&(*inst)].first=prev;//compute IN from previous OUT-value
                    //===========================================================
                    // errs()<<WHITEB<<"\nINFLOW:"<<prev[0];
                    int matching_context_label=0;
                    matching_context_label=check_if_context_already_exists(new_context_object);
                    if(matching_context_label>0)//step 15
                    {
                        errs()<<BLUEB"\nExisting context found! It has label:"<<matching_context_label<<RST;
                        //step 16 and 17
                        new_outflow_forward=context_label_to_context_object_map[matching_context_label].second.second.first;
                        
                        // Just using the prev variable to print info in next line. 
                        // The variable prev will be overwritten later with the OUT value
                        // at the end of this "if" block.
                        prev=new_outflow_forward;
                        // errs()<<WHITEB<<"\nNew Outflow before meet:"<<prev[0]<<RST;
                        
                        pair<int,Instruction*>mypair=make_pair(current_context_label,&(*inst));
                    
                        //step 14
                        context_transition_graph[mypair]=matching_context_label;

                        //===========================================================
                        //step 18 and 19
                        
                        /*
                        At the call instruction, the value at IN should be splitted into two components.
                        The purely global component is given to the callee while the mixed component is propagated
                        to OUT of this instruction after executing computeOUTfromIN() on it.
                        */
                        F value_on_which_local_flow_function_is_used=getMixedComponentForward(IN[&(*inst)].first);
                        F value_to_be_propagated_to_out_of_instruction=computeOutFromIn(*inst);
                        /*
                        At the OUT of this instruction, the value from END of callee procedure is to be merged
                        with the local(mixed) value propagated from IN. Note that this merging "isn't" 
                        exactly (necessarily) the meet between these two values.
                        */
                        F merged_value_at_out_of_instruction=getMergedValuesForward(new_outflow_forward,value_to_be_propagated_to_out_of_instruction);

                        // errs()<<WHITEB<<"\nMerged Value:"<<merged_value_at_out_of_instruction[0]<<RST;
                        // errs()<<WHITEB<<"\nPrev OUT Value:"<<OUT[&(*inst)].first[0]<<RST;
                        /*
                        As explained in ip-vasco,pdf, we need to perform meet with the original value of OUT
                        of this instruction to avoid the oscillation problem.
                        */
                        OUT[&(*inst)].first=performMeetForward(merged_value_at_out_of_instruction,OUT[&(*inst)].first);

                        // OUT[&(*inst)].first=performMeetForward(performMeetForward(computeOutFromIn(*inst),new_outflow_forward),OUT[&(*inst)].first);

                        
                        //local: Now computing local info of OUT[I]
                        // OUT[&(*inst)].first=computeOutFromIn(*inst);
                        prev=OUT[&(*inst)].first;
                        // errs()<<WHITEB<<"\nNew Outflow after meet:"<<prev[0]<<RST;
                        //===========================================================
                    }
                    else//step 20
                    {
                        //creating a new context
                        INIT_CONTEXT(new_context_object);//step 21

                        pair<int,Instruction*>mypair=make_pair(current_context_label,&(*inst));
                        //step 14
                        context_transition_graph[mypair]=context_label_counter;
                        return;
                        //===========================================================
                        OUT[&(*inst)].first=computeOutFromIn(*inst);
                        prev=OUT[&(*inst)].first;
                        //===========================================================
                    }
                }
                else
                {
                    errs()<<"\n"<<*inst;
                    IN[&(*inst)].first=prev;//compute IN from previous OUT-value
                    OUT[&(*inst)].first=computeOutFromIn(*inst);
                    prev=OUT[&(*inst)].first;
                }
            }
            CS_BB_OUT[current_pair].first=prev;
        }
        else//step 22
        {
            //step 23
            //NormalFlowFunction
            CS_BB_OUT[current_pair].first=NormalFlowFunctionForward(current_pair);
        }
        bool changed=false;
        if(!EqualDataFlowValuesForward(previous_value_at_out_of_this_node,CS_BB_OUT[current_pair].first))
        {
            changed=true;
        }
        if(changed)//step 24
        {
            //not yet converged
            for(auto succ_bb:successors(bb))//step 25
            {
                errs()<<"\nSucc BB: ";
                succ_bb->printAsOperand(errs(),false);
                errs() << "\t"; //Label of Basic block

                //step 26
                if(!forward_worklist_contains_this_entry[make_pair(current_context_label,succ_bb)])
                {
                    forward_worklist.push(make_pair(current_context_label,succ_bb));
                    forward_worklist_contains_this_entry[make_pair(current_context_label,succ_bb)]=true;
                }
                if(!backward_worklist_contains_this_entry[make_pair(current_context_label,succ_bb)])
                {
                    backward_worklist.push(make_pair(current_context_label,succ_bb));
                    backward_worklist_contains_this_entry[make_pair(current_context_label,succ_bb)]=true;
                }
            }

        }
        if(bb==&function.back())//step 27
        {
            //last node/exit node
            
            //step 28
            // errs()<<WHITEB<<"\nOUTFLOW VALUE(before):"<<context_label_to_context_object_map[current_context_label].second.second.first[0];
            
            // context_label_to_context_object_map[current_context_label].second.second.first=CS_BB_OUT[current_pair].first;//setting forward outflow
            context_label_to_context_object_map[current_context_label].second.second.first=getPurelyGlobalComponentForward(CS_BB_OUT[current_pair].first);//setting forward outflow
            
            // errs()<<WHITEB<<"\nOUTFLOW VALUE(after):"<<context_label_to_context_object_map[current_context_label].second.second.first[0];
            
            for(auto context_inst_pairs:context_transition_graph)//step 29
            {
                if(context_inst_pairs.second==current_context_label)//matching the called function
                {
                    //step 30
                    errs()<<CYANB<<"\ncaller basic block label:"<<context_inst_pairs.first.first<<RST;
                    BasicBlock *bb=context_inst_pairs.first.second->getParent();
                    pair<int,BasicBlock*>context_bb_pair=make_pair(context_inst_pairs.first.first,bb);
                    if(!forward_worklist_contains_this_entry[context_bb_pair])
                    {
                        forward_worklist.push(context_bb_pair);
                        forward_worklist_contains_this_entry[context_bb_pair]=true;
                    }
                    if(!backward_worklist_contains_this_entry[context_bb_pair])
                    {
                        backward_worklist.push(context_bb_pair);
                        backward_worklist_contains_this_entry[context_bb_pair]=true;
                    }
                    // forward_worklist.push(context_bb_pair);
                    // backward_worklist.push(context_bb_pair);
                }
            }

        }
        // errs()<<WHITEB<<"\nBB_OUT"<<CS_BB_OUT[current_pair].first[0]<<RST;
    }
    // else
    // {
        //worklist is empty
        errs()<<GREENB"\nNothing left to process in forward direction."RST;
    // }
}

template <class F,class B>
F Analysis<F,B>::NormalFlowFunctionForward(pair<int,BasicBlock*> current_pair_of_context_label_and_bb)
{
    BasicBlock &b=*(current_pair_of_context_label_and_bb.second);
    F prev=CS_BB_IN[current_pair_of_context_label_and_bb].first;
    //traverse a basic block in forward direction
    for(auto inst=b.begin();inst!=b.end();inst++)
    {
        errs()<<"\n"<<*inst;
        IN[&(*inst)].first=prev;//compute IN from previous OUT-value
        OUT[&(*inst)].first=computeOutFromIn(*inst);
        prev=OUT[&(*inst)].first;
    }
    return prev;
}

template <class F,class B>
int Analysis<F,B>::check_if_context_already_exists(pair<Function*,pair<pair<F,B>,pair<F,B>>> new_context_object)
{
    // errs()<<CYANB"\nINSIDE METHOD CHECK FOR EXISTING CONTEXT. Total existing contexts="<<ProcedureContext.size()<<RST;
    if(std::is_same<B, NoAnalysisType>::value)
    {
        //forward only
        // F some_irrelevant_local_value=getBoundaryInformationForward();
        for(auto set_itr:ProcedureContext)
        {
            pair<Function*,pair<pair<F,B>,pair<F,B>>> current_object= context_label_to_context_object_map[set_itr];
            F new_context_values=new_context_object.second.first.first;
            F current_context_values=current_object.second.first.first;
            if(new_context_object.first==current_object.first&&EqualDataFlowValuesForward(new_context_values,current_context_values))
            {
                return set_itr;
            }
        }
    }
    else if(std::is_same<F, NoAnalysisType>::value)
    {
        //backward only
        // B some_irrelevant_local_value=getBoundaryInformationBackward(); 
        for(auto set_itr:ProcedureContext)
        {
            pair<Function*,pair<pair<F,B>,pair<F,B>>> current_object= context_label_to_context_object_map[set_itr];
            // errs()<<YELLOWB<<"\nExisting val:"<<current_object.second.first.second[0]<<" Curr Val:"<<new_context_object.second.first.second[0]<<" Exis func:"<<current_object.first->getName()<<" Curr Func:"<<new_context_object.first->getName()<<" Set itr:"<<set_itr;
            B new_context_values= new_context_object.second.first.second;
            B current_context_values= current_object.second.first.second;
            if(new_context_object.first==current_object.first&&EqualDataFlowValuesBackward(new_context_values,current_context_values))
            {
                errs()<<YELLOWB<<"\nMatching Context found!";
                return set_itr;
            }
        }
        errs()<<REDB<<"\nNO Matching Context found!";
    }
    else
    {
        //bidirectional
        // F some_irrelevant_local_value_forward=getBoundaryInformationForward();
        // B some_irrelevant_local_value_backward=getBoundaryInformationBackward();
        int i=0;
        for(auto set_itr:ProcedureContext)
        {
            // errs()<<GREENB"\n"<<set_itr;
            pair<Function*,pair<pair<F,B>,pair<F,B>>> current_object= context_label_to_context_object_map[set_itr];
            
            F new_context_values_forward = new_context_object.second.first.first;
            F current_context_values_forward = current_object.second.first.first;
            B new_context_values_backward = new_context_object.second.first.second;
            B current_context_values_backward = current_object.second.first.second;
            
            // errs()<<"\nNewForward";
            // printDataFlowValuesForward(new_context_values_forward);
            // errs()<<"\nCurrentForward";
            // printDataFlowValuesForward(current_context_values_forward);
            errs()<<"\n-------------------------------";
            if(new_context_object.first==current_object.first&&EqualDataFlowValuesBackward(new_context_values_backward,current_context_values_backward)&&EqualDataFlowValuesForward(new_context_values_forward,current_context_values_forward))
            {
                errs()<<YELLOWB<<"\nMatching Context found!";
                return set_itr;
            }
        }
        errs()<<REDB<<"\nNO Matching Context found!"; 
    }
    return false;
}

template <class F,class B>
void Analysis<F,B>::printWorklistMaps()
{
	errs()<<REDB<<"\n-----------------------------------------";
	errs()<<WHITEB;
	for(auto x:backward_worklist_contains_this_entry)
	{
	    errs()<<"\n";
	    errs()<<x.first.first<<" ";
	    BasicBlock *bb=x.first.second;
	    bb->printAsOperand(errs(),false);
	    errs()<<x.second;
	}
	errs()<<REDB<<"\n-----------------------------------------";
	errs()<<RST;
}

template <class F,class B>
void Analysis<F,B>::doAnalysisBackward()
{
    while(!backward_worklist.empty())//step 2
    {
        //step 3 and 4
        pair<int,BasicBlock*> current_pair=backward_worklist.top();
        int current_context_label;
        BasicBlock *bb;
        current_context_label=backward_worklist.top().first;
        bb=backward_worklist.top().second;
        backward_worklist.pop();
        backward_worklist_contains_this_entry[make_pair(current_context_label,bb)]=false;

        BasicBlock &b=*bb;
        Function *f=context_label_to_context_object_map[current_context_label].first;
        Function &function=*f;
        errs()<<BLUEB"\nContext Label: "<<current_context_label<<" BasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<" Function Name: "<<f->getName()<<" WS:"<<backward_worklist.size()<<RST;
        
        //step 5
        if(bb!=(&function.back()))
        {
            errs()<<"\nNon-Exit Block";
            //step 6
            CS_BB_OUT[current_pair].second=getInitialisationValueBackward();

            //step 7 and 8
            for(auto succ_bb:successors(bb))
            {
                errs()<<"\nSucc BB: ";
                succ_bb->printAsOperand(errs(),false);
                errs() << "\t"; //Label of Basic block
                CS_BB_OUT[current_pair].second=performMeetBackward(CS_BB_OUT[current_pair].second,CS_BB_IN[make_pair(current_pair.first,succ_bb)].second);
            }
        }
        else
        {
            errs()<<"\nExit Block";
            //In value of this node is same as INFLOW value
            // errs()<<context_label_to_context_object_map[current_context_label].second.first.first[0]; //won't work
            CS_BB_OUT[current_pair].second=context_label_to_context_object_map[current_context_label].second.first.second;
        }
        
        //step 9
        B previous_value_at_in_of_this_node=CS_BB_IN[current_pair].second;
        //step 10
        bool contains_a_method_call=false;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            Instruction &I=*inst;
            if ( CallInst *fnn = dyn_cast<CallInst>(&I))
            {
                contains_a_method_call=true;
                errs()<<REDB"\nMethod Call found in basic block: "<<inst->getParent()->getName()<<RST;
                break;
            }
        }
        // errs()<<MAGENTAB"\nContains a method call: "<<contains_a_method_call<<RST;
        if(contains_a_method_call)
        {
            B prev=CS_BB_OUT[current_pair].second;
            int call_number=0;
            
            //step 11
            for(auto inst=b.rbegin();inst!=b.rend();inst++)
            {
                Instruction &I=*inst;
                if ( CallInst *ci = dyn_cast<CallInst>(&I))
                {

                    Function* target_function= ci->getCalledFunction();
                    // errs()<<REDB"\nCalled Function: "<<target_function->getName()<<RST;
                    if((*target_function).size()==0)
                    {
                        continue;
                    }
                    call_number++;
                    errs()<<"\n"<<*inst;
                    
                    /*
                    At the call instruction, the value at OUT should be splitted into two components:
                    1) Purely Global and 2) Mixed.
                    The purely global component is given to the end of callee.
                    */
                    // //step 12
                    F new_inflow_forward;
                    B new_inflow_backward=getPurelyGlobalComponentBackward(prev);//prev;
                    F new_outflow_forward;
                    B new_outflow_backward;
                    
                    // //step 12
                    
                    //step 13
                    pair<Function*,pair<pair<F,B>,pair<F,B>>> new_context_object=make_pair(target_function,make_pair(make_pair(new_inflow_forward,new_inflow_backward),make_pair(new_outflow_forward,new_outflow_backward)));

                    //===========================================================
                    OUT[&(*inst)].second=prev;//compute OUT from previous IN-value
                    //===========================================================
                    // errs()<<WHITEB<<"\nINFLOW:"<<prev[0];
                    int matching_context_label=0;
                    matching_context_label=check_if_context_already_exists(new_context_object);
                    if(matching_context_label>0)//step 15
                    {
                        errs()<<BLUEB"\nExisting context found! It has label:"<<matching_context_label<<RST;
                        //step 16 and 17
                        new_outflow_backward=context_label_to_context_object_map[matching_context_label].second.second.second;
                        prev=new_outflow_backward;
                        // errs()<<WHITEB<<"\nNew Outflow before meet:"<<prev.first[0]<<RST;
                        pair<int,Instruction*>mypair=make_pair(current_context_label,&(*inst));
                        
                        //step 14
                        context_transition_graph[mypair]=matching_context_label;

                        //===========================================================
                        //step 18 and 19
                        /*
                        At the call instruction, the value at OUT should be splitted into two components.
                        The purely global component is given to the callee while the mixed component is propagated
                        to IN of this instruction after executing computeINfromOUT() on it.
                        */
                        
                        B value_on_which_local_flow_function_is_used=getMixedComponentBackward(OUT[&(*inst)].second);
                        B value_to_be_propagated_to_in_of_instruction=computeInFromOut(*inst);
                        /*
                        At the IN of this instruction, the value from START of callee procedure is to be merged
                        with the local(mixed) value propagated from OUT. Note that this merging "isn't" 
                        exactly (necessarily) the meet between these two values.
                        */
                        B merged_value_at_in_of_instruction=getMergedValuesBackward(new_outflow_backward,value_to_be_propagated_to_in_of_instruction);

                        // errs()<<WHITEB<<"\nMerged Value:"<<merged_value_at_in_of_instruction[0]<<RST;
                        // errs()<<WHITEB<<"\nPrev IN Value:"<<IN[&(*inst)].second[0]<<RST;
                        /*
                        As explained in ip-vasco,pdf, we need to perform meet with the original value of IN
                        of this instruction to avoid the oscillation problem.
                        */
                        IN[&(*inst)].second=performMeetBackward(merged_value_at_in_of_instruction,IN[&(*inst)].second);
                        
                        //local
                        // IN[&(*inst)].second=computeInFromOut(*inst);
                        prev=IN[&(*inst)].second;
                        // errs()<<WHITEB<<"\nNew Inflow after meet:"<<prev[0]<<RST;
                        
                        //===========================================================
                    }
                    else//step 20
                    {
                        //creating a new context
                        INIT_CONTEXT(new_context_object);//step 21

                        pair<int,Instruction*>mypair=make_pair(current_context_label,&(*inst));
                        //step 14
                        context_transition_graph[mypair]=context_label_counter;
                        return;
                        //===========================================================
                        IN[&(*inst)].second=computeInFromOut(*inst);
                        prev=IN[&(*inst)].second;
                        //===========================================================
                    }
                }
                else
                {
                    errs()<<"\n"<<*inst;
                    OUT[&(*inst)].second=prev;//compute OUT from previous IN-value
                    IN[&(*inst)].second=computeInFromOut(*inst);
                    prev=IN[&(*inst)].second;
                }
            }
            CS_BB_IN[current_pair].second=prev;
        }
        else//step 22
        {
            //step 23
            //NormalFlowFunction
            CS_BB_IN[current_pair].second=NormalFlowFunctionBackward(current_pair);
            
        }
        bool changed=false;
        if(!EqualDataFlowValuesBackward(previous_value_at_in_of_this_node,CS_BB_IN[current_pair].second))
        {
            changed=true;
        }
        if(changed)//step 24
        {
            //not yet converged
            for(auto pred_bb:predecessors(bb))//step 25
            {
                errs()<<"\nPred BB: ";
                pred_bb->printAsOperand(errs(),false);
                errs() << "\t"; //Label of Basic block

                //step 26
                if(!forward_worklist_contains_this_entry[make_pair(current_context_label,pred_bb)])
                {
                    forward_worklist.push(make_pair(current_context_label,pred_bb));
                    forward_worklist_contains_this_entry[make_pair(current_context_label,pred_bb)]=true;
                }
                if(!backward_worklist_contains_this_entry[make_pair(current_context_label,pred_bb)])
                {
                    backward_worklist.push(make_pair(current_context_label,pred_bb));
                    backward_worklist_contains_this_entry[make_pair(current_context_label,pred_bb)]=true;
                }
                // forward_worklist.push(make_pair(current_context_label,pred_bb));
                // backward_worklist.push(make_pair(current_context_label,pred_bb));  
            }

        }
        
        if(bb==&function.getEntryBlock())//step 27
        {
            //first node/start node
            
            //step 28
            // errs()<<WHITEB<<"\nBACKWARD OUTFLOW VALUE(before):"<<context_label_to_context_object_map[current_context_label].second.second.second[0];
            
            // context_label_to_context_object_map[current_context_label].second.second.second=CS_BB_IN[current_pair].second;//setting backward outflow
            context_label_to_context_object_map[current_context_label].second.second.second=getPurelyGlobalComponentBackward(CS_BB_IN[current_pair].second);//setting backward outflow
            
            // errs()<<WHITEB<<"\nBACKWARD OUTFLOW VALUE(after):"<<context_label_to_context_object_map[current_context_label].second.second.second[0];
            
            for(auto context_inst_pairs:context_transition_graph)//step 29
            {
                if(context_inst_pairs.second==current_context_label)//matching the called function
                {
                    //step 30
                    
                    errs()<<CYANB<<"\ncaller context label:"<<context_inst_pairs.first.first<<RST;
                    
                    BasicBlock *bb=context_inst_pairs.first.second->getParent();
                    pair<int,BasicBlock*>context_bb_pair=make_pair(context_inst_pairs.first.first,bb);
                    if(!forward_worklist_contains_this_entry[context_bb_pair])
                    {
                        forward_worklist.push(context_bb_pair);
                        forward_worklist_contains_this_entry[context_bb_pair]=true;
                    }
                    if(!backward_worklist_contains_this_entry[context_bb_pair])
                    {
                        backward_worklist.push(context_bb_pair);
                        backward_worklist_contains_this_entry[context_bb_pair]=true;
                    }
                    // forward_worklist.push(context_bb_pair);
                    // backward_worklist.push(context_bb_pair);
                    
                }
            }

        }
        
        // errs()<<WHITEB<<"\nBB_IN"<<CS_BB_IN[current_pair].second[0]<<RST;
    }
    // else
    // {
        //worklist is empty
        errs()<<GREENB"\nNothing left to process in backward direction."RST;
    // }
}

template <class F,class B>
B Analysis<F,B>::NormalFlowFunctionBackward(pair<int,BasicBlock*> current_pair_of_context_label_and_bb)
{
    BasicBlock &b=*(current_pair_of_context_label_and_bb.second);
    B prev=CS_BB_OUT[current_pair_of_context_label_and_bb].second;
    //traverse a basic block in forward direction
    for(auto inst=b.rbegin();inst!=b.rend();inst++)
    {
        errs()<<"\n"<<*inst;
        OUT[&(*inst)].second=prev;//compute OUT from previous IN-value
        IN[&(*inst)].second=computeInFromOut(*inst);
        prev=IN[&(*inst)].second;
    }
    return prev;
}

template<class F,class B>
void Analysis<F,B>::performFormalToActualMapping(Function &function)
{
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        errs()<<GREENB;
        BasicBlock &b=*BB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<WHITEB;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            errs()<<"\n";
            errs()<<(*inst);
        }
    }
    errs()<<GREENB"\n----------------------------------------------"RST;
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        errs()<<GREENB;
        BasicBlock &b=*BB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<WHITEB;
        // Instruction &I;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            errs()<<"\n";
            errs()<<(*inst);
            Instruction &I=*inst;
            if ( CallInst *fnn = dyn_cast<CallInst>(&I))
            {
                CallBase* cb=dyn_cast<CallBase>(&I);
                errs()<<CYANB<<"\nNumber of Operands:"<<cb->getNumArgOperands()<<RST;
                int nop=cb->getNumArgOperands();
                errs()<<YELLOWB"\n======================="RST;
                if(nop>0)
                {
                    errs()<<CYANB<<"\n"<<cb->getArgOperand(0)->getName()<<RST;
                    errs()<<CYANB<<"\n"<<cb->getCalledOperand()->getName()<<RST;
                    Function* target_function= fnn->getCalledFunction();
                    errs()<<REDB"\nCalled Function: "<<target_function->getName()<<RST;
                    if((*target_function).size()==0)
                    {
                        errs()<<REDB"\nInbuilt!"<<RST;
                        continue;//this is an inbuilt function so doesnt need to be processed.
                    }
                    // errs()<<CYANB<<"\n"<<target_function->getOperand(0)->getName()<<RST;
                    // IRBuilder<>irb()=Get_Builder();
                    
                    int i=0;
                    for(Function::arg_iterator argi=target_function->arg_begin(),arge=target_function->arg_end(); argi!=arge;argi++,i++)
                    {
                        errs()<<GREENB<<"\n"<<cb->getArgOperand(i)->getName()<<RST;
                        errs()<<MAGENTAB<< argi->getName()<<"\n";
                        Value *fp=dyn_cast<Value>(argi);
                        // irb.createStore(cb->getArgOperand(i),argi);
                        StoreInst* si=new StoreInst(cb->getArgOperand(i),fp,&I);
                    }

                }
                errs()<<YELLOWB"\n======================="RST;
            }

        }
    }
    errs()<<GREENB"\n----------------------------------------------"RST;
    
    
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        errs()<<YELLOWB;
        BasicBlock &b=*BB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<WHITEB;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            errs()<<"\n";
            errs()<<(*inst);
        }
    }
    errs()<<RST;
                
}


template <class F,class B>
void Analysis<F,B>::performSplittingBB(Function &function)
{
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        errs()<<GREENB;
        BasicBlock &b=*BB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<WHITEB;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            errs()<<"\n";
            errs()<<(*inst);
        }
    }






//================================================================================================    
    // int flag=0;
    // for(BasicBlock *BB:post_order(&function.getEntryBlock()))
    // {
    //     // errs()<<GREENB;
    //     BasicBlock &b=*BB;
    //     // errs()<<"\nBasicBlock: ";
    //     // b.printAsOperand(errs(),false);
    //     // errs()<<RST;
    //     // errs()<<CYANB;
    //     Instruction *I=&(*(b.begin()));
    //     for(auto inst=b.begin();inst!=b.end();inst++)
    //     {
    //         // errs()<<"\n";
    //         // errs()<<(*inst);
    //         Instruction &ins=*inst;
    //         if (isa<CallInst>(ins))
    //         {
    //             I=&(*inst);
    //             b.splitBasicBlock(I);
    //             flag=1;
    //             break;
    //         }
    //     }
    //     if(flag==1)
    //     {
    //         errs()<<MAGENTAB<<"\nSplitting On:"<<*I;
    //         flag=0;
    //         // break;
    //     }
    // }
    //================================================================================================
    errs()<<CYANB"\n----------------------------------------------------------------\n";
    int flag=0;
    Instruction *I=NULL;
    bool previousInstructionWasSplitted=false;
    bool previousInstructionWasCallInstruction=false;
    map<Instruction *,bool>isSplittedOnThisInstruction;
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        // errs()<<GREENB;
        BasicBlock &b=*BB;
        // if(b.size()==2)
        //     continue;
        // errs()<<"\nBasicBlock: ";
        // b.printAsOperand(errs(),false);
        // errs()<<WHITEB;
        previousInstructionWasSplitted=true;
        previousInstructionWasCallInstruction=false;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            I=&(*inst);
            if(inst==b.begin())
            {
                if (isa<CallInst>(*I))
                {
                    isSplittedOnThisInstruction[I]=false;
                    previousInstructionWasCallInstruction=true;
                    previousInstructionWasSplitted=true;//creating a false positive
                }
                continue;    
            }
            // errs()<<"\n";
            // errs()<<(*inst);
            if(isa<BranchInst>(*I))
            {
                
            }
            else if (isa<CallInst>(*I))
            {
                isSplittedOnThisInstruction[I]=true;
                previousInstructionWasCallInstruction=true;
                previousInstructionWasSplitted=true;
            }
            else
            {
                if(previousInstructionWasSplitted)
                {
                    if(previousInstructionWasCallInstruction)
                    {
                        isSplittedOnThisInstruction[I]=1;
                        previousInstructionWasSplitted=true;
                    }
                    else
                    {
                        previousInstructionWasSplitted=false;
                    }
                }
                else
                {
                    //do nothing
                }
                previousInstructionWasCallInstruction=false;
            }
        }
    }
    BasicBlock *containingBB;
    
    for(auto split_here:isSplittedOnThisInstruction)
    {
        // errs()<<"\n";
        // errs()<<*(split_here.first);
        if(split_here.second==false)//no splitting to be done
            continue;
        containingBB=split_here.first->getParent();
        containingBB->splitBasicBlock(split_here.first);
    }
    // errs()<<RST;
errs()<<CYANB"\n----------------------------------------------------------------\n";
//================================================================================================
   /* errs()<<MAGENTAB"\n----------------------------------------------------------------\n";
    int flag=0;
    map<Instruction *,bool>isSplittedOnThisInstruction;
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        BasicBlock &b=*BB;
        errs()<<GREENB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<RST;
        // errs()<<CYANB;
        Instruction *I=NULL;
        BasicBlock *bb=BB;
        while(1)
        {
                
            auto inst=(*bb).begin();
            while(1)//(auto inst=b.begin();inst!=b.end();inst++)
            {
                errs()<<"\n"<<YELLOWB;
                errs()<<(*inst);
                errs()<<RST;
                Instruction &ins=*inst;
                I=&(*inst);
                if (isa<CallInst>(ins)&&isSplittedOnThisInstruction[I]==false)
                {
                    isSplittedOnThisInstruction[I]=true;
                    bb=(*bb).splitBasicBlock(I);
                    flag=1;
                    break;
                }
                inst++;
                if(inst==(*bb).end())
                    break;
            }
            if(flag==1)
            {
                errs()<<MAGENTAB<<"\nSplitting On:"<<*I<<RST;
                flag=0;
                // break;
            }
            else
            {
                break;
            }
        }
    }
    errs()<<MAGENTAB"\n----------------------------------------------------------------\n";
    */
    for(BasicBlock *BB:inverse_post_order(&function.back()))
    {
        errs()<<YELLOWB;
        BasicBlock &b=*BB;
        errs()<<"\nBasicBlock: ";
        b.printAsOperand(errs(),false);
        errs()<<WHITEB;
        for(auto inst=b.begin();inst!=b.end();inst++)
        {
            errs()<<"\n";
            errs()<<(*inst);
        }
    }
    errs()<<RST;
    
}

template <class F,class B>
void Analysis<F,B>::drawSuperGraph(Module &M)
{
    filebuf fb;
    fb.open ("../testcases/supergraph/supergraph1.dot",ios::out);
    ostream os(&fb);
    // os << "Test sentence\n";
    string str;
    llvm::raw_string_ostream ss(str);
    string str1;
    llvm::raw_string_ostream ss1(str1);
    int cnt=0;
    os<< "digraph{\ngraph[fontsize=40];\n";
    for(Function &function:M)
    {
        os << "subgraph cluster_"<<cnt++<<"{\n";
        os << "style=filled;\ncolor=lightgrey;\nnode [style=filled,fillcolor=white,color=black,fontsize=40];\n";
        for(BasicBlock *BB:inverse_post_order(&function.back()))
        {
            BasicBlock &b=*BB;
            os << "BB";
            b.printAsOperand(ss1);
            os<<str1;
            string bbname=b.getName().str();
            os << " [label = \"BasicBlock "<<bbname<<":\\l";
            for(auto inst=b.begin();inst!=b.end();inst++)
            {
                Instruction &I=*inst;
                // os<<I<<"\n";
                
                ss << I;
                os << ss.str() << "\n";
                str="";
            }
            os<<"\"];\n";
        }
        string procname=function.getName().str();
        os <<"label=" << "\"Procedure : "<<procname<<"\";\n";
        os << "}\n";
        
    }
    os<< "label="<<"supergraph\n"<<"}\n";
    fb.close();
}







#endif

