#include <iostream>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Instruction.def"

using namespace llvm;

namespace{

  bool getFirstPassSig( Instruction*inst ){
	  unsigned OpCode = inst->getOpcode();
	  switch (OpCode) {
	    case Ret:    return true;
	    case Br:     return true;
	    case Switch: return true;
	    case IndirectBr: return true;
	    case Invoke: return true;
	    case Resume: return true;
	    case Unreachable: return true;
	    
	    case Alloca:        return true;
	    case Load:          return true;
	    case Store:         return true;
	    case AtomicCmpXchg: return true;
	    case AtomicRMW:     return true;
	    case Fence:         return true;
	    case GetElementPtr: return true;
	    
	    case Call:           return true;
	    
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

