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

	typedef iplist<BasicBlock> BasicBlockListType;
	typedef BasicBlockListType::iterator block_iter;
	typedef iplist<Instruction> InstListType;
	typedef InstListType::iterator inst_iter;

	struct Slicing : public FunctionPass{
		static char ID;
		Slicing() : FunctionPass(ID) {}
		virtual bool runOnFunction(Function &F){
			/*
			   BasicBlockListType &my_blocks = F.getBasicBlockList();  
			   block_iter blocks = my_blocks.begin(); 
			   for( blocks = my_blocks.begin() ; blocks != my_blocks.end() ; ++blocks){
			   InstListType &Instructions = blocks->getInstList();
			   inst_iter inst = Instructions.begin();
			   for(inst = Instructions.begin() ; inst != Instructions.end(); ++inst){
			   const char *name = inst->getOpcodeName();
			   unsigned int num_operands = inst->getNumOperands();
			   std::cout<<"Instruction Name "<<name<<" Operands : "<<num_operands<<""<<std::endl;
			   }


			   }
			   return false;
			 */

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
					bool sig = i->getSignificance();
					std::cout<<"Instruction Name "<<name<<" Operands : "<<num_operands<<" "<<id<<" "<<std::endl;
				}	
			}
			return false;
		}	



	};

}

char Slicing::ID = 0;
static RegisterPass<Slicing> Slice("Slice","Slicing Pass Per Function",false,false);

