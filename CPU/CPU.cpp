#include "CPU.h"

CPU::CPU(Bus const& bus) : mBus(bus)
{
	initInstructionSet();
}

void CPU::initInstructionSet() 
{
	InstructionFactory instructionFactory = InstructionFactory();

	mInstructionSet =
	{
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "instruction1", &Instruction1BitOperation::instruction1, 1)
	};
}

void CPU::executeOpcode()
{
	(mInstructionSet[0]->getFunctionPointer())();
}