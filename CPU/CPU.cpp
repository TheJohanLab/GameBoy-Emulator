#include "CPU.h"

CPU::CPU()
{

}

CPU::CPU(Bus const& bus) : mBus(bus)
{
	initInstructionSet();
}

void CPU::initInstructionSet() 
{
	InstructionFactory instructionFactory = InstructionFactory();

	mInstructionSet =
	{
		instructionFactory.createInstruction(InstructionEnum::ICPUCONTROL, "NOP", &InstructionCPUControl::nop, 4),					//0x00
		instructionFactory.createInstruction(InstructionEnum::I1BITOPERATION, "BIT 0,B", &Instruction1BitOperation::bit_0cB, 1),	//CB40

	};
}

u8 CPU::executeOpcode(u16 opcode) const
{
	CPU cpu;
	(mInstructionSet[opcode]->getFunctionPointer())(cpu);
	std::cout << mInstructionSet[opcode]->getName() << "\n";
	
	return mInstructionSet[opcode]->getClockCycle();
}

