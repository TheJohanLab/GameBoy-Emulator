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
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,B", &Instruction1BitOperation::bit_0cB, 1), //CB40

	};
}

void CPU::executeOpcode()
{
	(mInstructionSet[0]->getFunctionPointer())();
}

