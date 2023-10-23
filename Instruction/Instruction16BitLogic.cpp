#include "Instruction16BitLogic.h"

Instruction16BitLogic::Instruction16BitLogic(std::string const & name, void (*pInstruction)(), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}