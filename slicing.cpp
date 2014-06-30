#include <iostream>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/User.h"

using namespace llvm;

namespace{

  bool getFirstPassSig( Instruction*inst ){
	  unsigned OpCode = inst->getOpcode();
	  switch (OpCode) {
	    case Instruction::Ret:    return true;
	    case Instruction::Br:     return true;
	    case Instruction:: Switch: return true;
	    case Instruction:: IndirectBr: return true;
	    case Instruction:: Invoke: return true;
	    case Instruction:: Resume: return true;
	    case Instruction:: Unreachable: return true;
	    
	    case Instruction:: Alloca:        return true;
	    case Instruction:: Load:          return true;
	    case Instruction:: Store:         return true;
	    case Instruction:: AtomicCmpXchg: return true;
	    case Instruction:: AtomicRMW:     return true;
	    case Instruction:: Fence:         return true;
	    case Instruction:: GetElementPtr: return true;
	    
	    case Instruction:: Call:           return true;
	    
	    default: return false;
	    
	  }
	  return false;
	}
	
  
	typedef iplist<BasicBlock> BasicBlockListType;
	typedef BasicBlockListType::iterator block_iter;
	typedef iplist<Instruction> InstListType;
	typedef InstListType::iterator inst_iter;

	struct Slicing : public FunctionPass{
		static char ID;
		Slicing() : FunctionPass(ID) {}
		virtual bool runOnFunction(Function &F){
			std::cout << "\n*********************************\n";
			std::cout<<"Slicing Pass per function Starts\n";
			errs().write_escaped(F.getName()) <<"\n";
 			std::cout<<"********************************** \n";
			for (Function::iterator bb = F.begin(), bbe = F.end(); bb != bbe; ++bb) {
				BasicBlock &b = *bb;
				for (BasicBlock::iterator i = b.begin(), ie = b.end(); i != ie; ++i) {
					const char *name = i->getOpcodeName();
					unsigned int num_operands = i->getNumOperands();
					Type *inst_type = i->getType();
					Type::TypeID id = inst_type->getTypeID();
					
					// Initialize significance of already known instructions (branch,load,store etc)
					i->setSignificance(getFirstPassSig(i));
					
					std::cout<<"Instruction Name "<<name<<" Operands : "<<num_operands<<" "<<id<<" "<<std::endl;
				}	
			}
			return false;
		}	



	};

}

char Slicing::ID = 0;
static RegisterPass<Slicing> Slice("Slice","Slicing Pass Per Function",false,false);

