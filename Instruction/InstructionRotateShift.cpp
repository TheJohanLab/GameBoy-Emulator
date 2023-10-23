#include "InstructionRotateShift.h"

InstructionRotateShift::InstructionRotateShift(std::string const & name, void (*pInstruction)(), u8 ClockCycle)
{
	mName = name;
	pmInstruction = pInstruction;
	mClockCycle = ClockCycle;

}