#include "Instruction16BitLogic.h"

Instruction16BitLogic::Instruction16BitLogic(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void Instruction16BitLogic::INC_BC(CPU& cpu)
{
}

void Instruction16BitLogic::ADD_HLcBC(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_BC(CPU& cpu)
{
}

void Instruction16BitLogic::INC_DE(CPU& cpu)
{
}

void Instruction16BitLogic::ADD_HLcDE(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_DE(CPU& cpu)
{
}

void Instruction16BitLogic::INC_HL(CPU& cpu)
{
}

void Instruction16BitLogic::ADD_HLcHL(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_HL(CPU& cpu)
{
}

void Instruction16BitLogic::INC_SP(CPU& cpu)
{
}

void Instruction16BitLogic::ADD_HLcSP(CPU& cpu)
{
}

void Instruction16BitLogic::DEC_SP(CPU& cpu)
{
}

void Instruction16BitLogic::ADD_SPcr8(CPU& cpu)
{
}
