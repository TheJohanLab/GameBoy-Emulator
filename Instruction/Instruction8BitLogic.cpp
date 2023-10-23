#include "Instruction8BitLogic.h"

Instruction8BitLogic::Instruction8BitLogic(std::string const & name, void (*pInstruction)(), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}