#include "Instruction1BitOperation.h"

Instruction1BitOperation::Instruction1BitOperation(std::string const & name, void (*pInstruction)(), u8 cycles)
{
	mName = name;
	pmInstruction = pInstruction;

}

void Instruction1BitOperation::bit_0cB()
{
	std::cout << "instr 1" << "\n";
}