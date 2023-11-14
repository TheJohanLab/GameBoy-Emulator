#include "InstructionCPUControl.h"

InstructionCPUControl::InstructionCPUControl(std::string const & name, void (*pInstruction)(CPU & cpu), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}

void InstructionCPUControl::nop(CPU & cpu)
{

}