#include "InstructionFactory.h"

InstructionFactory::InstructionFactory()
{

}


Instruction* InstructionFactory::createInstruction(InstructionEnum instructionEnum, const char* name, u8 (*pInstruction)(CPU & cpu), u8 clockCycles) const
{
	switch(instructionEnum) 
	{
		case InstructionEnum::I1BITOPERATION: return new Instruction1BitOperation(name, pInstruction, clockCycles); break;
		case InstructionEnum::I8BITLOAD		: return new Instruction1BitOperation(name, pInstruction, clockCycles); break;
		case InstructionEnum::I8BITLOGIC    : return new Instruction8BitLogic(name, pInstruction, clockCycles);     break;
		case InstructionEnum::I16BITLOAD    : return new Instruction16BitLoad(name, pInstruction, clockCycles);     break;
		case InstructionEnum::I16BITLOGIC   : return new Instruction16BitLogic(name, pInstruction, clockCycles);    break;
		case InstructionEnum::ICPUCONTROL   : return new InstructionCPUControl(name, pInstruction, clockCycles);    break;
		case InstructionEnum::IJUMP         : return new InstructionJump(name, pInstruction, clockCycles);          break;
		case InstructionEnum::IROTATESHIFT  : return new InstructionRotateShift(name, pInstruction, clockCycles);   break;
	}
}