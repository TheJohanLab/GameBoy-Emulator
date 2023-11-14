#include "Instruction1BitOperation.h"

Instruction1BitOperation::Instruction1BitOperation(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles)
{
	mName = name;
	pmInstruction = pInstruction;
	
}

void Instruction1BitOperation::bit_0cB(CPU & cpu)
{
	cpu.setAF(12);
}