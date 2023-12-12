#include "Instruction16BitLoad.h"

Instruction16BitLoad::Instruction16BitLoad(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction16BitLoad::LD_BCcd16(CPU& cpu)
{
}

void Instruction16BitLoad::LD_pa16qcSP(CPU& cpu)
{
}

void Instruction16BitLoad::LD_DEcd16(CPU& cpu)
{
}

void Instruction16BitLoad::LD_HLcd16(CPU& cpu)
{
}

void Instruction16BitLoad::LD_SPcd16(CPU& cpu)
{
}

void Instruction16BitLoad::POP_BC(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_BC(CPU& cpu)
{
}

void Instruction16BitLoad::POP_DE(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_DE(CPU& cpu)
{
}

void Instruction16BitLoad::POP_HL(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_HL(CPU& cpu)
{
}

void Instruction16BitLoad::POP_AF(CPU& cpu)
{
}

void Instruction16BitLoad::PUSH_AF(CPU& cpu)
{
}

void Instruction16BitLoad::LDHL_SPcr8(CPU& cpu)
{
}

void Instruction16BitLoad::LD_SPcHL(CPU& cpu)
{
}
