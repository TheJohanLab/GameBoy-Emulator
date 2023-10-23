#include "Instruction16BitLoad.h"

Instruction16BitLoad::Instruction16BitLoad(std::string const & name, void (*pInstruction)(), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}